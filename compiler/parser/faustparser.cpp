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
     ONDEMAND = 361,
     UPSAMPLING = 362,
     DOWNSAMPLING = 363,
     STRING = 364,
     FSTRING = 365,
     IDENT = 366,
     EXTRA = 367,
     DECLARE = 368,
     CASE = 369,
     ARROW = 370,
     ASSERTBOUNDS = 371,
     LOWEST = 372,
     HIGHEST = 373,
     FLOATMODE = 374,
     DOUBLEMODE = 375,
     QUADMODE = 376,
     FIXEDPOINTMODE = 377,
     BDOC = 378,
     EDOC = 379,
     BEQN = 380,
     EEQN = 381,
     BDGM = 382,
     EDGM = 383,
     BLST = 384,
     ELST = 385,
     BMETADATA = 386,
     EMETADATA = 387,
     DOCCHAR = 388,
     NOTICE = 389,
     LISTING = 390,
     LSTTRUE = 391,
     LSTFALSE = 392,
     LSTDEPENDENCIES = 393,
     LSTMDOCTAGS = 394,
     LSTDISTRIBUTED = 395,
     LSTEQ = 396,
     LSTQ = 397
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
#define ONDEMAND 361
#define UPSAMPLING 362
#define DOWNSAMPLING 363
#define STRING 364
#define FSTRING 365
#define IDENT 366
#define EXTRA 367
#define DECLARE 368
#define CASE 369
#define ARROW 370
#define ASSERTBOUNDS 371
#define LOWEST 372
#define HIGHEST 373
#define FLOATMODE 374
#define DOUBLEMODE 375
#define QUADMODE 376
#define FIXEDPOINTMODE 377
#define BDOC 378
#define EDOC 379
#define BEQN 380
#define EEQN 381
#define BDGM 382
#define EDGM 383
#define BLST 384
#define ELST 385
#define BMETADATA 386
#define EMETADATA 387
#define DOCCHAR 388
#define NOTICE 389
#define LISTING 390
#define LSTTRUE 391
#define LSTFALSE 392
#define LSTDEPENDENCIES 393
#define LSTMDOCTAGS 394
#define LSTDISTRIBUTED 395
#define LSTEQ 396
#define LSTQ 397




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
    error << FAUSTfilename << ":" << FAUSTlineno << " : ERROR : " << msg << endl;
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
    Tree exp;
    char* str;
    std::string* cppstr;
    bool b;
    int numvariant;
}
/* Line 193 of yacc.c.  */
#line 494 "faustparser.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 507 "faustparser.cpp"

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
#define YYLAST   811

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  143
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  68
/* YYNRULES -- Number of rules.  */
#define YYNRULES  245
/* YYNRULES -- Number of states.  */
#define YYNSTATES  526

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   397

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
     135,   136,   137,   138,   139,   140,   141,   142
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
     555,   557,   559,   561,   563,   567,   571,   575,   579,   583,
     585,   587,   589,   591,   593,   602,   611,   620,   629,   634,
     639,   644,   649,   654,   663,   671,   679,   684,   689,   702,
     715,   728,   735,   742,   749,   758,   767,   774,   780,   788,
     798,   810,   815,   822,   831,   842,   844,   846,   850,   852,
     855,   862,   864,   866,   868,   870
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     144,     0,    -1,   145,    -1,    -1,   145,   147,   152,    -1,
      -1,   146,   147,   164,    -1,    -1,   147,   148,    -1,   119,
      -1,   120,    -1,   121,    -1,   122,    -1,    -1,   149,   165,
      -1,   151,    -1,   150,     8,   151,    -1,    75,    -1,    76,
      -1,    18,    75,    -1,    18,    76,    -1,    17,    75,    -1,
      17,    76,    -1,    92,    83,   179,    84,    81,    -1,   113,
     175,   178,    81,    -1,   113,   175,   175,   178,    81,    -1,
     164,    -1,   123,   153,   124,    -1,    -1,   153,   154,    -1,
     155,    -1,   156,    -1,   157,    -1,   158,    -1,   159,    -1,
     163,    -1,    -1,   155,   133,    -1,   125,   171,   126,    -1,
     127,   171,   128,    -1,   134,    -1,   129,   160,   130,    -1,
      -1,   160,   161,    -1,   138,   141,   142,   162,   142,    -1,
     139,   141,   142,   162,   142,    -1,   140,   141,   142,   162,
     142,    -1,   136,    -1,   137,    -1,   131,   175,   132,    -1,
     166,    83,   176,    84,    90,   171,    81,    -1,   166,    90,
     171,    81,    -1,     1,    81,    -1,   167,    90,   171,    81,
      -1,     1,    81,    -1,   174,    -1,    28,   174,    -1,   174,
      -1,   168,     8,   174,    -1,   179,    -1,   179,     7,   177,
      -1,   169,    -1,   170,     8,   169,    -1,   171,     3,    85,
     146,    86,    -1,   171,     4,    85,   149,    86,    -1,   171,
       4,    85,   149,    89,   146,    86,    -1,   171,     8,   171,
      -1,   171,     7,   171,    -1,   171,     6,   171,    -1,   171,
       5,   171,    -1,   171,     9,   171,    -1,   172,    -1,   172,
      18,   172,    -1,   172,    17,   172,    -1,   172,    25,   172,
      -1,   172,    24,   172,    -1,   172,    23,   172,    -1,   172,
      26,   172,    -1,   172,    27,   172,    -1,   172,    28,    -1,
     172,    29,   174,    -1,   172,    22,   172,    -1,   172,    16,
     172,    -1,   172,    21,   172,    -1,   172,    20,   172,    -1,
     172,    19,   172,    -1,   172,    15,   172,    -1,   172,    14,
     172,    -1,   172,    12,   172,    -1,   172,    11,   172,    -1,
     172,    13,   172,    -1,   172,    10,   172,    -1,   172,    83,
     176,    84,    -1,   172,    87,   146,    88,    -1,   173,    -1,
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
     116,    -1,   117,    -1,   118,    -1,   174,    -1,    17,   174,
      -1,    83,   171,    84,    -1,    78,    83,   168,    84,    29,
      83,   171,    84,    -1,    87,   170,    91,   171,    88,    -1,
     114,    85,   207,    86,    -1,   190,    -1,   191,    -1,   192,
      -1,    93,    83,   179,    84,    -1,    94,    83,   179,    84,
      -1,    95,    85,   145,    86,    -1,    96,    85,   150,    86,
      -1,    97,    83,   177,     8,   177,    84,    -1,    97,    83,
     177,     8,   177,     8,   171,    84,    -1,   193,    -1,   194,
      -1,   195,    -1,   196,    -1,   197,    -1,   198,    -1,   199,
      -1,   200,    -1,   201,    -1,   202,    -1,   203,    -1,   181,
      -1,   182,    -1,   183,    -1,   184,    -1,   185,    -1,   186,
      -1,   187,    -1,   188,    -1,   189,    -1,   111,    -1,   111,
      -1,   177,    -1,   176,     8,   177,    -1,   177,     7,   177,
      -1,   177,     6,   177,    -1,   177,     5,   177,    -1,   177,
       9,   177,    -1,   172,    -1,   109,    -1,   109,    -1,   109,
      -1,   110,    -1,   100,    83,   174,     8,   177,     8,   171,
      84,    -1,   101,    83,   174,     8,   177,     8,   171,    84,
      -1,   102,    83,   174,     8,   177,     8,   171,    84,    -1,
     103,    83,   174,     8,   177,     8,   171,    84,    -1,   104,
      83,   171,    84,    -1,   105,    83,   171,    84,    -1,   106,
      83,   171,    84,    -1,   107,    83,   171,    84,    -1,   108,
      83,   171,    84,    -1,    35,    83,   204,     8,   180,     8,
     178,    84,    -1,    36,    83,   209,   175,     8,   180,    84,
      -1,    37,    83,   209,   175,     8,   180,    84,    -1,    38,
      83,   179,    84,    -1,    39,    83,   179,    84,    -1,    40,
      83,   179,     8,   177,     8,   177,     8,   177,     8,   177,
      84,    -1,    41,    83,   179,     8,   177,     8,   177,     8,
     177,     8,   177,    84,    -1,    42,    83,   179,     8,   177,
       8,   177,     8,   177,     8,   177,    84,    -1,    43,    83,
     179,     8,   171,    84,    -1,    44,    83,   179,     8,   171,
      84,    -1,    45,    83,   179,     8,   171,    84,    -1,    47,
      83,   179,     8,   177,     8,   177,    84,    -1,    46,    83,
     179,     8,   177,     8,   177,    84,    -1,    48,    83,   179,
       8,   177,    84,    -1,   209,   205,    83,   206,    84,    -1,
     209,   205,    16,   205,    83,   206,    84,    -1,   209,   205,
      16,   205,    16,   205,    83,   206,    84,    -1,   209,   205,
      16,   205,    16,   205,    16,   205,    83,   206,    84,    -1,
     209,   205,    83,    84,    -1,   209,   205,    16,   205,    83,
      84,    -1,   209,   205,    16,   205,    16,   205,    83,    84,
      -1,   209,   205,    16,   205,    16,   205,    16,   205,    83,
      84,    -1,   111,    -1,   210,    -1,   206,     8,   210,    -1,
     208,    -1,   207,   208,    -1,    83,   176,    84,   115,   171,
      81,    -1,    32,    -1,    33,    -1,    32,    -1,    33,    -1,
      34,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   365,   365,   368,   369,   372,   373,   376,   377,   380,
     381,   382,   383,   386,   387,   394,   395,   398,   399,   400,
     401,   402,   403,   406,   407,   408,   409,   410,   413,   414,
     417,   418,   419,   420,   421,   422,   425,   426,   429,   432,
     435,   438,   441,   442,   445,   446,   447,   450,   451,   454,
     457,   458,   459,   462,   463,   466,   469,   472,   473,   476,
     477,   480,   481,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   495,   496,   497,   498,   499,   500,   501,   502,
     503,   505,   506,   507,   509,   510,   512,   513,   514,   515,
     516,   517,   519,   520,   522,   525,   526,   528,   529,   531,
     532,   534,   535,   537,   538,   540,   541,   543,   544,   545,
     546,   547,   548,   550,   551,   552,   554,   555,   557,   558,
     559,   560,   561,   562,   564,   565,   566,   568,   569,   570,
     571,   572,   573,   574,   576,   577,   578,   579,   580,   581,
     583,   584,   585,   587,   588,   590,   591,   592,   593,   595,
     596,   598,   599,   601,   602,   603,   605,   606,   608,   609,
     615,   618,   620,   621,   622,   623,   624,   625,   626,   627,
     628,   629,   630,   631,   632,   633,   634,   635,   636,   637,
     638,   639,   641,   642,   643,   644,   646,   647,   648,   649,
     650,   653,   656,   659,   660,   663,   664,   665,   666,   667,
     670,   673,   676,   677,   682,   686,   690,   694,   698,   701,
     704,   707,   710,   715,   719,   723,   728,   731,   734,   737,
     740,   743,   746,   749,   753,   756,   759,   766,   767,   768,
     769,   771,   772,   773,   774,   777,   780,   781,   784,   785,
     788,   792,   793,   796,   797,   798
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
  "ONDEMAND", "UPSAMPLING", "DOWNSAMPLING", "STRING", "FSTRING", "IDENT",
  "EXTRA", "DECLARE", "CASE", "ARROW", "ASSERTBOUNDS", "LOWEST", "HIGHEST",
  "FLOATMODE", "DOUBLEMODE", "QUADMODE", "FIXEDPOINTMODE", "BDOC", "EDOC",
  "BEQN", "EEQN", "BDGM", "EDGM", "BLST", "ELST", "BMETADATA", "EMETADATA",
  "DOCCHAR", "NOTICE", "LISTING", "LSTTRUE", "LSTFALSE", "LSTDEPENDENCIES",
  "LSTMDOCTAGS", "LSTDISTRIBUTED", "LSTEQ", "LSTQ", "$accept", "program",
  "stmtlist", "deflist", "variantlist", "variant", "reclist", "vallist",
  "number", "statement", "doc", "docelem", "doctxt", "doceqn", "docdgm",
  "docntc", "doclst", "lstattrlist", "lstattrdef", "lstattrval", "docmtd",
  "definition", "recinition", "defname", "recname", "params", "modentry",
  "modlist", "expression", "infixexp", "primitive", "ident", "name",
  "arglist", "argument", "string", "uqstring", "fstring", "fpar", "fseq",
  "fsum", "fprod", "finputs", "foutputs", "fondemand", "fupsampling",
  "fdownsampling", "ffunction", "fconst", "fvariable", "button",
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
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   143,   144,   145,   145,   146,   146,   147,   147,   148,
     148,   148,   148,   149,   149,   150,   150,   151,   151,   151,
     151,   151,   151,   152,   152,   152,   152,   152,   153,   153,
     154,   154,   154,   154,   154,   154,   155,   155,   156,   157,
     158,   159,   160,   160,   161,   161,   161,   162,   162,   163,
     164,   164,   164,   165,   165,   166,   167,   168,   168,   169,
     169,   170,   170,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   174,   175,   176,   176,   177,   177,   177,   177,   177,
     178,   179,   180,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   204,   204,
     204,   204,   204,   204,   204,   205,   206,   206,   207,   207,
     208,   209,   209,   210,   210,   210
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
       1,     1,     1,     1,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     8,     8,     8,     8,     4,     4,
       4,     4,     4,     8,     7,     7,     4,     4,    12,    12,
      12,     6,     6,     6,     8,     8,     6,     5,     7,     9,
      11,     4,     6,     8,    10,     1,     1,     3,     1,     2,
       6,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     7,     1,     0,     0,     0,   191,     0,     9,
      10,    11,    12,    28,     8,     4,    26,     0,    55,    52,
       0,   192,     0,    36,     0,     0,   201,     0,   200,     0,
       0,    27,     0,     0,    42,     0,    40,    29,    30,    31,
      32,    33,    34,    35,   123,   121,   120,   122,   119,   118,
     114,   108,   107,   117,   116,   115,   113,   111,   110,   109,
     137,   112,   103,   104,   105,   106,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     124,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,    95,    96,     0,   101,
     102,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     153,   154,   155,   199,    94,   156,     0,   193,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   162,   163,   164,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,     0,    71,     0,     0,    24,     0,     0,     0,     0,
      37,    99,   100,   157,    97,    98,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    61,     0,    59,     0,     0,     3,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    79,     0,
       0,     5,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,    23,    25,    38,    39,
      41,     0,     0,     0,    43,    49,   241,   242,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    57,   158,     0,     0,     0,     0,
       0,     7,     0,     0,    17,    18,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     238,    91,    89,    88,    90,    87,    86,    82,    73,    72,
      85,    84,    83,    81,    76,    75,    74,    77,    78,    80,
       0,     7,   194,     0,   197,   196,   195,   198,     5,    13,
      69,    68,    67,    66,    70,     0,     0,     0,     0,   235,
       0,     0,     0,   216,   217,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    62,     0,    60,   165,
     166,   167,    21,    22,    19,    20,     0,   168,     0,     0,
       0,     0,     0,   208,   209,   210,   211,   212,     0,   161,
     239,    92,    93,     0,     0,     7,     0,     0,     0,     0,
     202,   203,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    58,     0,   160,    16,
       0,     0,     0,     0,     0,     0,     6,    50,    63,     0,
       0,    64,     5,    14,     0,    47,    48,     0,     0,     0,
       0,     0,   243,   244,   245,   231,     0,   236,     0,     0,
       0,     0,     0,   221,   222,   223,     0,     0,   226,     0,
       0,   169,     0,     0,     0,     0,     0,    54,    56,     7,
       0,    44,    45,    46,     0,     0,     0,     0,   227,   214,
     215,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    65,     0,   213,     0,   232,     0,   237,
       0,     0,     0,   225,   224,   159,   170,   204,   205,   206,
     207,   240,    53,     0,     0,   228,     0,     0,     0,     0,
     233,     0,     0,     0,     0,     0,   229,     0,     0,     0,
     234,     0,   218,   219,   220,   230
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   321,   383,    14,   386,   286,   287,    15,
      23,    37,    38,    39,    40,    41,    42,   168,   254,   427,
      43,    16,   423,    17,   424,   273,   192,   193,   161,   133,
     134,   135,    22,   136,   137,    30,   194,   392,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   258,   340,   436,   299,   300,   259,   437
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -389
static const yytype_int16 yypact[] =
{
    -389,    25,    49,  -389,     3,    15,    16,  -389,    -4,  -389,
    -389,  -389,  -389,  -389,  -389,  -389,  -389,   -10,  -389,  -389,
      35,  -389,   -30,   270,   450,   450,  -389,    29,  -389,    45,
      71,  -389,   450,   450,  -389,    -4,  -389,  -389,    14,  -389,
    -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,
    -389,   189,    42,  -389,  -389,  -389,  -389,  -389,  -389,  -389,
    -389,  -389,  -389,  -389,  -389,  -389,    81,    95,   101,   126,
     191,   210,   214,   216,   226,   289,   313,   315,   317,   329,
    -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,
    -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,
    -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,   340,  -389,
    -389,   450,    35,   343,   353,   230,   328,   356,  -389,  -389,
     364,   367,   374,   375,   395,   396,   401,   444,   448,   335,
    -389,  -389,  -389,   616,  -389,  -389,    13,   437,  -389,  -389,
    -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,
    -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,
    -389,   594,   616,   352,   451,  -389,    39,     7,   278,   179,
    -389,  -389,  -389,  -389,  -389,  -389,   134,   134,   134,    35,
      35,    35,    35,    35,    35,    35,    35,    35,    35,    35,
     326,    59,  -389,    11,   527,    35,    35,  -389,    66,   450,
     326,   326,   326,   326,   450,   450,   450,   450,   450,   452,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,  -389,   326,
     450,  -389,   450,   446,   450,   450,   450,   450,   474,   475,
     450,   450,   450,   450,   450,  -389,  -389,  -389,  -389,  -389,
    -389,   421,   422,   424,  -389,  -389,  -389,  -389,   617,   535,
      -4,    -4,   563,   564,   641,   648,   655,   662,   664,   665,
     666,   673,   680,    43,  -389,  -389,    35,   450,   450,   611,
     613,   612,   136,   202,  -389,  -389,    12,  -389,   533,   692,
     693,   694,   761,    84,   221,   228,   279,   323,   450,    23,
    -389,   688,   688,   688,   688,   688,   688,   699,   699,   699,
     275,   275,   275,   275,   275,   275,   275,   332,    75,  -389,
      61,   682,   437,   450,   437,   437,   125,  -389,  -389,  -389,
     646,   646,   162,   271,  -389,   630,   631,   632,   182,  -389,
      36,   773,   775,  -389,  -389,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   326,   755,  -389,    52,   437,  -389,
    -389,  -389,  -389,  -389,  -389,  -389,    66,  -389,   450,   450,
     450,   450,   450,  -389,  -389,  -389,  -389,  -389,    62,  -389,
    -389,  -389,  -389,    17,   601,   706,    22,   177,   177,   177,
    -389,  -389,   777,   535,   287,   182,   182,   653,   660,   671,
     330,   337,   348,   678,   685,    28,  -389,   710,  -389,  -389,
      21,   724,   729,   734,   739,   679,  -389,  -389,  -389,   714,
     326,  -389,  -389,  -389,   707,  -389,  -389,   654,   656,   657,
      45,    37,  -389,  -389,  -389,  -389,    64,  -389,   716,   717,
     450,   450,   450,  -389,  -389,  -389,   450,   450,  -389,   450,
     450,  -389,   450,   450,   450,   450,   450,  -389,  -389,   718,
     450,  -389,  -389,  -389,   719,   535,   350,   234,  -389,  -389,
    -389,   744,   749,   754,    69,   124,   361,   372,   566,   573,
     580,   587,   608,  -389,   615,  -389,    38,  -389,    93,  -389,
     450,   450,   450,  -389,  -389,  -389,  -389,  -389,  -389,  -389,
    -389,  -389,  -389,   535,   354,  -389,   759,   771,   782,   722,
    -389,   205,   450,   450,   450,   357,  -389,   154,   266,   301,
    -389,   206,  -389,  -389,  -389,  -389
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -389,  -389,   605,  -322,     0,  -389,  -389,  -389,   440,  -389,
    -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,     4,
    -389,   425,  -389,  -389,  -389,  -389,   531,  -389,    -1,   -25,
    -389,    20,   -13,  -213,  -196,   -28,    74,    10,  -389,  -389,
    -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,
    -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,
    -389,  -389,  -388,   -93,  -389,   510,   232,   344
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
     162,   164,     4,   288,     5,   431,   385,   162,   162,    29,
     238,   239,   240,   241,   242,   243,   244,   320,     5,   276,
     366,   232,   169,   419,    18,     3,   234,   235,   236,   450,
     237,   166,   167,   234,   235,   236,   322,   237,   324,   325,
     326,   327,   238,   239,   240,   241,   242,   243,   244,    -2,
     420,   354,   393,   465,   503,   238,   239,   240,   241,   242,
     243,   244,   238,   239,   240,   241,   242,   243,   244,   232,
     232,   173,   467,    24,   234,   235,   236,   486,   237,    28,
      25,    21,   358,   282,   283,   378,   162,   238,   239,   240,
     241,   242,   243,   244,    27,     6,    19,   233,   367,    20,
     459,   467,   277,   228,   229,   451,   298,    21,   421,   379,
     191,   422,   448,   163,     7,   509,     8,   174,   175,   394,
     466,   504,     9,    10,    11,    12,    13,   355,     7,   234,
     235,   236,   236,   237,   237,   249,     9,    10,    11,    12,
     408,   284,   285,   275,    26,   381,   415,   170,   468,   397,
     398,   399,   165,   493,    28,   403,   404,   405,   230,   234,
     235,   236,   231,   237,   176,   248,   256,   257,   373,   242,
     243,   244,   410,   411,   412,   413,   414,   505,   177,   162,
     162,   162,   162,   162,   178,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   293,   294,   295,   296,   297,   494,   179,
     274,   362,   363,   467,   467,   162,   162,   162,   162,   162,
     289,   290,   291,   292,   238,   239,   240,   241,   242,   243,
     244,   238,   239,   240,   241,   242,   243,   244,   522,   330,
     331,   332,   333,   334,   471,   472,   473,   341,   342,   319,
     474,   475,   162,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   171,   172,   432,   433,   434,   279,
     280,   234,   235,   236,   180,   237,   357,   364,   365,   243,
     244,     4,   238,   239,   240,   241,   242,   243,   244,   516,
     525,   390,   391,   181,   506,   507,   508,   182,   162,   183,
       7,   226,   227,   228,   229,   374,   234,   235,   236,   184,
     237,   255,   375,   425,   426,   197,   517,   518,   519,   432,
     433,   434,   384,   162,   162,   162,   238,   239,   240,   241,
     242,   243,   244,   238,   239,   240,   241,   242,   243,   244,
     238,   239,   240,   241,   242,   243,   244,   400,   401,   402,
     523,   238,   239,   240,   241,   242,   243,   244,   230,   227,
     228,   229,   231,   376,   238,   239,   240,   241,   242,   243,
     244,   435,   185,   488,   406,   238,   239,   240,   241,   242,
     243,   244,   432,   433,   434,   524,   432,   433,   434,   432,
     433,   434,   428,   429,    31,    32,   186,    33,   187,    34,
     188,    35,   464,    18,    36,   438,   439,   377,   250,   260,
     261,   511,   189,   198,   443,   230,   251,   252,   253,   231,
     209,   444,   521,   190,   162,   162,   195,   162,   162,   162,
     162,   162,   445,   246,   487,   162,   196,     7,   510,   199,
     458,   520,   234,   235,   236,   495,   237,   200,   476,   477,
     201,   478,   479,   480,   481,   482,   496,   202,   203,   484,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,   204,   205,
      62,    63,    64,    65,   206,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   207,   108,   109,
     110,   208,   247,   111,   278,   298,   323,   112,   234,   235,
     236,   368,   237,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   328,
     329,     7,   335,   336,   129,   337,   130,   131,   132,   238,
     239,   240,   241,   242,   243,   244,   238,   239,   240,   241,
     242,   243,   244,   238,   239,   240,   241,   242,   243,   244,
     238,   239,   240,   241,   242,   243,   244,   238,   239,   240,
     241,   242,   243,   244,   238,   239,   240,   241,   242,   243,
     244,   238,   239,   240,   241,   242,   243,   244,   238,   239,
     240,   241,   242,   243,   244,   338,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   339,   343,   344,   345,
     497,   240,   241,   242,   243,   244,   346,   498,   234,   235,
     236,   440,   237,   347,   499,   234,   235,   236,   441,   237,
     348,   500,   349,   350,   351,   245,   234,   235,   236,   442,
     237,   352,   417,   234,   235,   236,   446,   237,   353,   501,
     234,   235,   236,   447,   237,   359,   502,   360,   361,   230,
     369,   370,   371,   231,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   234,
     235,   236,   452,   237,   234,   235,   236,   453,   237,   234,
     235,   236,   454,   237,   234,   235,   236,   455,   237,   234,
     235,   236,   490,   237,   234,   235,   236,   491,   237,   234,
     235,   236,   492,   237,   234,   235,   236,   512,   237,   372,
     382,   230,   387,   388,   389,   231,   234,   235,   236,   513,
     237,   395,   230,   396,   407,   430,   231,   234,   235,   236,
     514,   237,   418,   449,   456,   457,   461,   460,   462,   463,
     469,   470,   281,   485,   483,   515,   409,   356,   416,   380,
       0,   489
};

static const yytype_int16 yycheck[] =
{
      25,    29,     2,   199,     1,   393,   328,    32,    33,    22,
       3,     4,     5,     6,     7,     8,     9,   230,     1,     8,
       8,     8,    35,     1,     4,     0,     5,     6,     7,     8,
       9,    32,    33,     5,     6,     7,   232,     9,   234,   235,
     236,   237,     3,     4,     5,     6,     7,     8,     9,     0,
      28,     8,    16,    16,    16,     3,     4,     5,     6,     7,
       8,     9,     3,     4,     5,     6,     7,     8,     9,     8,
       8,    51,     8,    83,     5,     6,     7,   465,     9,   109,
      90,   111,   278,    17,    18,   298,   111,     3,     4,     5,
       6,     7,     8,     9,    20,    92,    81,    84,    86,    83,
     422,     8,    91,    28,    29,    84,    83,   111,    86,    86,
     111,    89,    84,    84,   111,   503,   113,    75,    76,    83,
      83,    83,   119,   120,   121,   122,   123,    84,   111,     5,
       6,     7,     7,     9,     9,   128,   119,   120,   121,   122,
      88,    75,    76,    84,   109,    84,    84,   133,    84,   345,
     346,   347,    81,    84,   109,   351,   352,   353,    83,     5,
       6,     7,    87,     9,    83,   126,    32,    33,    84,     7,
       8,     9,   368,   369,   370,   371,   372,    84,    83,   204,
     205,   206,   207,   208,    83,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   204,   205,   206,   207,   208,    84,    83,
     190,    75,    76,     8,     8,   240,   241,   242,   243,   244,
     200,   201,   202,   203,     3,     4,     5,     6,     7,     8,
       9,     3,     4,     5,     6,     7,     8,     9,    84,   240,
     241,   242,   243,   244,   440,   441,   442,   260,   261,   229,
     446,   447,   277,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,    75,    76,    32,    33,    34,   195,
     196,     5,     6,     7,    83,     9,   277,    75,    76,     8,
       9,   281,     3,     4,     5,     6,     7,     8,     9,    84,
      84,   109,   110,    83,   490,   491,   492,    83,   323,    83,
     111,    26,    27,    28,    29,    84,     5,     6,     7,    83,
       9,   132,    84,   136,   137,    85,   512,   513,   514,    32,
      33,    34,   323,   348,   349,   350,     3,     4,     5,     6,
       7,     8,     9,     3,     4,     5,     6,     7,     8,     9,
       3,     4,     5,     6,     7,     8,     9,   348,   349,   350,
      84,     3,     4,     5,     6,     7,     8,     9,    83,    27,
      28,    29,    87,    84,     3,     4,     5,     6,     7,     8,
       9,    84,    83,   466,   354,     3,     4,     5,     6,     7,
       8,     9,    32,    33,    34,    84,    32,    33,    34,    32,
      33,    34,   388,   389,   124,   125,    83,   127,    83,   129,
      83,   131,   430,   383,   134,   395,   396,    84,   130,   177,
     178,   504,    83,    85,    84,    83,   138,   139,   140,    87,
      85,    84,   515,    83,   449,   450,    83,   452,   453,   454,
     455,   456,    84,    81,    84,   460,    83,   111,    84,    83,
     420,    84,     5,     6,     7,    84,     9,    83,   449,   450,
      83,   452,   453,   454,   455,   456,    84,    83,    83,   460,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    83,    83,
      30,    31,    32,    33,    83,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    83,    78,    79,
      80,    83,    81,    83,     7,    83,    90,    87,     5,     6,
       7,     8,     9,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,    85,
      85,   111,   141,   141,   114,   141,   116,   117,   118,     3,
       4,     5,     6,     7,     8,     9,     3,     4,     5,     6,
       7,     8,     9,     3,     4,     5,     6,     7,     8,     9,
       3,     4,     5,     6,     7,     8,     9,     3,     4,     5,
       6,     7,     8,     9,     3,     4,     5,     6,     7,     8,
       9,     3,     4,     5,     6,     7,     8,     9,     3,     4,
       5,     6,     7,     8,     9,     8,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,   111,    84,    84,     8,
      84,     5,     6,     7,     8,     9,     8,    84,     5,     6,
       7,     8,     9,     8,    84,     5,     6,     7,     8,     9,
       8,    84,     8,     8,     8,    81,     5,     6,     7,     8,
       9,     8,    81,     5,     6,     7,     8,     9,     8,    81,
       5,     6,     7,     8,     9,    84,    81,    84,    86,    83,
       8,     8,     8,    87,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,     5,
       6,     7,     8,     9,     5,     6,     7,     8,     9,     5,
       6,     7,     8,     9,     5,     6,     7,     8,     9,     5,
       6,     7,     8,     9,     5,     6,     7,     8,     9,     5,
       6,     7,     8,     9,     5,     6,     7,     8,     9,     8,
      88,    83,   142,   142,   142,    87,     5,     6,     7,     8,
       9,     8,    83,     8,    29,     8,    87,     5,     6,     7,
       8,     9,    86,    83,   115,    81,   142,    90,   142,   142,
      84,    84,   197,    84,    86,    83,   366,   276,   383,   299,
      -1,   467
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   144,   145,     0,   147,     1,    92,   111,   113,   119,
     120,   121,   122,   123,   148,   152,   164,   166,   174,    81,
      83,   111,   175,   153,    83,    90,   109,   179,   109,   175,
     178,   124,   125,   127,   129,   131,   134,   154,   155,   156,
     157,   158,   159,   163,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    30,    31,    32,    33,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    78,    79,
      80,    83,    87,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   114,
     116,   117,   118,   172,   173,   174,   176,   177,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   171,   172,    84,   178,    81,   171,   171,   160,   175,
     133,    75,    76,   174,    75,    76,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,   171,   169,   170,   179,    83,    83,    85,    85,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    85,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      83,    87,     8,    84,     5,     6,     7,     9,     3,     4,
       5,     6,     7,     8,     9,    81,    81,    81,   126,   128,
     130,   138,   139,   140,   161,   132,    32,    33,   204,   209,
     209,   209,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   168,   174,    84,     8,    91,     7,   179,
     179,   145,    17,    18,    75,    76,   150,   151,   177,   174,
     174,   174,   174,   171,   171,   171,   171,   171,    83,   207,
     208,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   174,
     176,   146,   177,    90,   177,   177,   177,   177,    85,    85,
     171,   171,   171,   171,   171,   141,   141,   141,     8,   111,
     205,   175,   175,    84,    84,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     8,    84,   169,   171,   177,    84,
      84,    86,    75,    76,    75,    76,     8,    86,     8,     8,
       8,     8,     8,    84,    84,    84,    84,    84,   176,    86,
     208,    84,    88,   147,   171,   146,   149,   142,   142,   142,
     109,   110,   180,    16,    83,     8,     8,   177,   177,   177,
     171,   171,   171,   177,   177,   177,   174,    29,    88,   151,
     177,   177,   177,   177,   177,    84,   164,    81,    86,     1,
      28,    86,    89,   165,   167,   136,   137,   162,   162,   162,
       8,   205,    32,    33,    34,    84,   206,   210,   180,   180,
       8,     8,     8,    84,    84,    84,     8,     8,    84,    83,
       8,    84,     8,     8,     8,     8,   115,    81,   174,   146,
      90,   142,   142,   142,   178,    16,    83,     8,    84,    84,
      84,   177,   177,   177,   177,   177,   171,   171,   171,   171,
     171,   171,   171,    86,   171,    84,   205,    84,   206,   210,
       8,     8,     8,    84,    84,    84,    84,    84,    84,    84,
      84,    81,    81,    16,    83,    84,   177,   177,   177,   205,
      84,   206,     8,     8,     8,    83,    84,   177,   177,   177,
      84,   206,    84,    84,    84,    84
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
#line 365 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); gGlobal->gResult = formatDefinitions((yyval.exp)); ;}
    break;

  case 3:
#line 368 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 4:
#line 369 "faustparser.y"
    { if (acceptdefinition((yyvsp[(2) - (3)].numvariant))) (yyval.exp) = cons ((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); else (yyval.exp)=(yyvsp[(1) - (3)].exp); ;}
    break;

  case 5:
#line 372 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 6:
#line 373 "faustparser.y"
    { if (acceptdefinition((yyvsp[(2) - (3)].numvariant))) (yyval.exp) = cons ((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); else (yyval.exp)=(yyvsp[(1) - (3)].exp);;}
    break;

  case 7:
#line 376 "faustparser.y"
    { (yyval.numvariant) = 0; ;}
    break;

  case 8:
#line 377 "faustparser.y"
    { (yyval.numvariant) = (yyvsp[(1) - (2)].numvariant) | (yyvsp[(2) - (2)].numvariant);;}
    break;

  case 9:
#line 380 "faustparser.y"
    { (yyval.numvariant) = 1;;}
    break;

  case 10:
#line 381 "faustparser.y"
    { (yyval.numvariant) = 2;;}
    break;

  case 11:
#line 382 "faustparser.y"
    { (yyval.numvariant) = 4;;}
    break;

  case 12:
#line 383 "faustparser.y"
    { (yyval.numvariant) = 8;;}
    break;

  case 13:
#line 386 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 14:
#line 387 "faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 15:
#line 394 "faustparser.y"
    { gGlobal->gWaveForm.push_back((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 16:
#line 395 "faustparser.y"
    { gGlobal->gWaveForm.push_back((yyvsp[(3) - (3)].exp)); ;}
    break;

  case 17:
#line 398 "faustparser.y"
    { (yyval.exp) = boxInt(str2int(FAUSTtext)); ;}
    break;

  case 18:
#line 399 "faustparser.y"
    { (yyval.exp) = boxReal(atof(FAUSTtext)); ;}
    break;

  case 19:
#line 400 "faustparser.y"
    { (yyval.exp) = boxInt(str2int(FAUSTtext)); ;}
    break;

  case 20:
#line 401 "faustparser.y"
    { (yyval.exp) = boxReal(atof(FAUSTtext)); ;}
    break;

  case 21:
#line 402 "faustparser.y"
    { (yyval.exp) = boxInt(-str2int(FAUSTtext)); ;}
    break;

  case 22:
#line 403 "faustparser.y"
    { (yyval.exp) = boxReal(-atof(FAUSTtext)); ;}
    break;

  case 23:
#line 406 "faustparser.y"
    { (yyval.exp) = importFile((yyvsp[(3) - (5)].exp)); ;}
    break;

  case 24:
#line 407 "faustparser.y"
    { declareMetadata((yyvsp[(2) - (4)].exp),(yyvsp[(3) - (4)].exp)); (yyval.exp) = gGlobal->nil; ;}
    break;

  case 25:
#line 408 "faustparser.y"
    { declareDefinitionMetadata((yyvsp[(2) - (5)].exp),(yyvsp[(3) - (5)].exp),(yyvsp[(4) - (5)].exp)); (yyval.exp) = gGlobal->nil; ;}
    break;

  case 26:
#line 409 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 27:
#line 410 "faustparser.y"
    { declareDoc((yyvsp[(2) - (3)].exp)); (yyval.exp) = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ ;}
    break;

  case 28:
#line 413 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; ;}
    break;

  case 29:
#line 414 "faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 30:
#line 417 "faustparser.y"
    { (yyval.exp) = docTxt((yyvsp[(1) - (1)].cppstr)->c_str()); delete (yyvsp[(1) - (1)].cppstr); ;}
    break;

  case 31:
#line 418 "faustparser.y"
    { (yyval.exp) = docEqn((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 32:
#line 419 "faustparser.y"
    { (yyval.exp) = docDgm((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 33:
#line 420 "faustparser.y"
    { (yyval.exp) = docNtc(); ;}
    break;

  case 34:
#line 421 "faustparser.y"
    { (yyval.exp) = docLst(); ;}
    break;

  case 35:
#line 422 "faustparser.y"
    { (yyval.exp) = docMtd((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 36:
#line 425 "faustparser.y"
    { (yyval.cppstr) = new string(); ;}
    break;

  case 37:
#line 426 "faustparser.y"
    { (yyval.cppstr) = &((yyvsp[(1) - (2)].cppstr)->append(FAUSTtext)); ;}
    break;

  case 38:
#line 429 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 39:
#line 432 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 40:
#line 435 "faustparser.y"
    { ;}
    break;

  case 41:
#line 438 "faustparser.y"
    { ;}
    break;

  case 42:
#line 441 "faustparser.y"
    { ;}
    break;

  case 43:
#line 442 "faustparser.y"
    { ;}
    break;

  case 44:
#line 445 "faustparser.y"
    { gGlobal->gLstDependenciesSwitch = (yyvsp[(4) - (5)].b); ;}
    break;

  case 45:
#line 446 "faustparser.y"
    { gGlobal->gStripDocSwitch = (yyvsp[(4) - (5)].b); gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; ;}
    break;

  case 46:
#line 447 "faustparser.y"
    { gGlobal->gLstDistributedSwitch = (yyvsp[(4) - (5)].b); ;}
    break;

  case 47:
#line 450 "faustparser.y"
    { (yyval.b) = true; ;}
    break;

  case 48:
#line 451 "faustparser.y"
    { (yyval.b) = false; ;}
    break;

  case 49:
#line 454 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 50:
#line 457 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp),cons((yyvsp[(3) - (7)].exp),(yyvsp[(6) - (7)].exp))); setDefProp((yyvsp[(1) - (7)].exp), FAUSTfilename, FAUSTlineno); ;}
    break;

  case 51:
#line 458 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(gGlobal->nil,(yyvsp[(3) - (4)].exp)));  setDefProp((yyvsp[(1) - (4)].exp), FAUSTfilename, FAUSTlineno); ;}
    break;

  case 52:
#line 459 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; FAUSTerr++; ;}
    break;

  case 53:
#line 462 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(gGlobal->nil,(yyvsp[(3) - (4)].exp))); setDefProp((yyvsp[(1) - (4)].exp), FAUSTfilename, FAUSTlineno); ;}
    break;

  case 54:
#line 463 "faustparser.y"
    { (yyval.exp) = gGlobal->nil; FAUSTerr++; ;}
    break;

  case 55:
#line 466 "faustparser.y"
    { (yyval.exp)=(yyvsp[(1) - (1)].exp); ;}
    break;

  case 56:
#line 469 "faustparser.y"
    { (yyval.exp)=(yyvsp[(2) - (2)].exp); ;}
    break;

  case 57:
#line 472 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 58:
#line 473 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 59:
#line 476 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 60:
#line 477 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 61:
#line 480 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 62:
#line 481 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 63:
#line 484 "faustparser.y"
    { (yyval.exp) = boxWithLocalDef((yyvsp[(1) - (5)].exp),formatDefinitions((yyvsp[(4) - (5)].exp))); ;}
    break;

  case 64:
#line 485 "faustparser.y"
    { (yyval.exp) = boxWithRecDef((yyvsp[(1) - (5)].exp),formatDefinitions((yyvsp[(4) - (5)].exp)), gGlobal->nil); ;}
    break;

  case 65:
#line 486 "faustparser.y"
    { (yyval.exp) = boxWithRecDef((yyvsp[(1) - (7)].exp),formatDefinitions((yyvsp[(4) - (7)].exp)),formatDefinitions((yyvsp[(6) - (7)].exp))); ;}
    break;

  case 66:
#line 487 "faustparser.y"
    { (yyval.exp) = boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 67:
#line 488 "faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 68:
#line 489 "faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 69:
#line 490 "faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 70:
#line 491 "faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 71:
#line 492 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 72:
#line 495 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxAdd()); ;}
    break;

  case 73:
#line 496 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxSub()); ;}
    break;

  case 74:
#line 497 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxMul()); ;}
    break;

  case 75:
#line 498 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxDiv()); ;}
    break;

  case 76:
#line 499 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxRem()); ;}
    break;

  case 77:
#line 500 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPow()); ;}
    break;

  case 78:
#line 501 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxDelay()); ;}
    break;

  case 79:
#line 502 "faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (2)].exp),boxDelay1()); ;}
    break;

  case 80:
#line 503 "faustparser.y"
    { (yyval.exp) = boxAccess((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 81:
#line 505 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxAND()); ;}
    break;

  case 82:
#line 506 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxOR()); ;}
    break;

  case 83:
#line 507 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxXOR()); ;}
    break;

  case 84:
#line 509 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxLeftShift()); ;}
    break;

  case 85:
#line 510 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxARightShift()); ;}
    break;

  case 86:
#line 512 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxLT()); ;}
    break;

  case 87:
#line 513 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxLE()); ;}
    break;

  case 88:
#line 514 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxGT()); ;}
    break;

  case 89:
#line 515 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxGE()); ;}
    break;

  case 90:
#line 516 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxEQ()); ;}
    break;

  case 91:
#line 517 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxNE()); ;}
    break;

  case 92:
#line 519 "faustparser.y"
    { (yyval.exp) = buildBoxAppl((yyvsp[(1) - (4)].exp),(yyvsp[(3) - (4)].exp)); ;}
    break;

  case 93:
#line 520 "faustparser.y"
    { (yyval.exp) = boxModifLocalDef((yyvsp[(1) - (4)].exp),formatDefinitions((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 94:
#line 522 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 95:
#line 525 "faustparser.y"
    { (yyval.exp) = boxInt(str2int(FAUSTtext)); ;}
    break;

  case 96:
#line 526 "faustparser.y"
    { (yyval.exp) = boxReal(atof(FAUSTtext)); ;}
    break;

  case 97:
#line 528 "faustparser.y"
    { (yyval.exp) = boxInt (str2int(FAUSTtext)); ;}
    break;

  case 98:
#line 529 "faustparser.y"
    { (yyval.exp) = boxReal(atof(FAUSTtext)); ;}
    break;

  case 99:
#line 531 "faustparser.y"
    { (yyval.exp) = boxInt ( -str2int(FAUSTtext) ); ;}
    break;

  case 100:
#line 532 "faustparser.y"
    { (yyval.exp) = boxReal( -atof(FAUSTtext) ); ;}
    break;

  case 101:
#line 534 "faustparser.y"
    { (yyval.exp) = boxWire(); ;}
    break;

  case 102:
#line 535 "faustparser.y"
    { (yyval.exp) = boxCut(); ;}
    break;

  case 103:
#line 537 "faustparser.y"
    { (yyval.exp) = boxDelay1(); ;}
    break;

  case 104:
#line 538 "faustparser.y"
    { (yyval.exp) = boxPrefix(); ;}
    break;

  case 105:
#line 540 "faustparser.y"
    { (yyval.exp) = boxIntCast(); ;}
    break;

  case 106:
#line 541 "faustparser.y"
    { (yyval.exp) = boxFloatCast(); ;}
    break;

  case 107:
#line 543 "faustparser.y"
    { (yyval.exp) = boxAdd(); ;}
    break;

  case 108:
#line 544 "faustparser.y"
    { (yyval.exp) = boxSub(); ;}
    break;

  case 109:
#line 545 "faustparser.y"
    { (yyval.exp) = boxMul(); ;}
    break;

  case 110:
#line 546 "faustparser.y"
    { (yyval.exp) = boxDiv(); ;}
    break;

  case 111:
#line 547 "faustparser.y"
    { (yyval.exp) = boxRem(); ;}
    break;

  case 112:
#line 548 "faustparser.y"
    { (yyval.exp) = boxDelay(); ;}
    break;

  case 113:
#line 550 "faustparser.y"
    { (yyval.exp) = boxAND(); ;}
    break;

  case 114:
#line 551 "faustparser.y"
    { (yyval.exp) = boxOR(); ;}
    break;

  case 115:
#line 552 "faustparser.y"
    { (yyval.exp) = boxXOR(); ;}
    break;

  case 116:
#line 554 "faustparser.y"
    { (yyval.exp) = boxLeftShift(); ;}
    break;

  case 117:
#line 555 "faustparser.y"
    { (yyval.exp) = boxARightShift(); ;}
    break;

  case 118:
#line 557 "faustparser.y"
    { (yyval.exp) = boxLT(); ;}
    break;

  case 119:
#line 558 "faustparser.y"
    { (yyval.exp) = boxLE(); ;}
    break;

  case 120:
#line 559 "faustparser.y"
    { (yyval.exp) = boxGT(); ;}
    break;

  case 121:
#line 560 "faustparser.y"
    { (yyval.exp) = boxGE(); ;}
    break;

  case 122:
#line 561 "faustparser.y"
    { (yyval.exp) = boxEQ(); ;}
    break;

  case 123:
#line 562 "faustparser.y"
    { (yyval.exp) = boxNE(); ;}
    break;

  case 124:
#line 564 "faustparser.y"
    { (yyval.exp) = boxAttach(); ;}
    break;

  case 125:
#line 565 "faustparser.y"
    { (yyval.exp) = boxEnable(); ;}
    break;

  case 126:
#line 566 "faustparser.y"
    { (yyval.exp) = boxControl(); ;}
    break;

  case 127:
#line 568 "faustparser.y"
    { (yyval.exp) = gGlobal->gAcosPrim->box(); ;}
    break;

  case 128:
#line 569 "faustparser.y"
    { (yyval.exp) = gGlobal->gAsinPrim->box(); ;}
    break;

  case 129:
#line 570 "faustparser.y"
    { (yyval.exp) = gGlobal->gAtanPrim->box(); ;}
    break;

  case 130:
#line 571 "faustparser.y"
    { (yyval.exp) = gGlobal->gAtan2Prim->box(); ;}
    break;

  case 131:
#line 572 "faustparser.y"
    { (yyval.exp) = gGlobal->gCosPrim->box(); ;}
    break;

  case 132:
#line 573 "faustparser.y"
    { (yyval.exp) = gGlobal->gSinPrim->box(); ;}
    break;

  case 133:
#line 574 "faustparser.y"
    { (yyval.exp) = gGlobal->gTanPrim->box(); ;}
    break;

  case 134:
#line 576 "faustparser.y"
    { (yyval.exp) = gGlobal->gExpPrim->box(); ;}
    break;

  case 135:
#line 577 "faustparser.y"
    { (yyval.exp) = gGlobal->gLogPrim->box(); ;}
    break;

  case 136:
#line 578 "faustparser.y"
    { (yyval.exp) = gGlobal->gLog10Prim->box(); ;}
    break;

  case 137:
#line 579 "faustparser.y"
    { (yyval.exp) = gGlobal->gPowPrim->box(); ;}
    break;

  case 138:
#line 580 "faustparser.y"
    { (yyval.exp) = gGlobal->gPowPrim->box(); ;}
    break;

  case 139:
#line 581 "faustparser.y"
    { (yyval.exp) = gGlobal->gSqrtPrim->box(); ;}
    break;

  case 140:
#line 583 "faustparser.y"
    { (yyval.exp) = gGlobal->gAbsPrim->box(); ;}
    break;

  case 141:
#line 584 "faustparser.y"
    { (yyval.exp) = gGlobal->gMinPrim->box(); ;}
    break;

  case 142:
#line 585 "faustparser.y"
    { (yyval.exp) = gGlobal->gMaxPrim->box(); ;}
    break;

  case 143:
#line 587 "faustparser.y"
    { (yyval.exp) = gGlobal->gFmodPrim->box(); ;}
    break;

  case 144:
#line 588 "faustparser.y"
    { (yyval.exp) = gGlobal->gRemainderPrim->box(); ;}
    break;

  case 145:
#line 590 "faustparser.y"
    { (yyval.exp) = gGlobal->gFloorPrim->box(); ;}
    break;

  case 146:
#line 591 "faustparser.y"
    { (yyval.exp) = gGlobal->gCeilPrim->box(); ;}
    break;

  case 147:
#line 592 "faustparser.y"
    { (yyval.exp) = gGlobal->gRintPrim->box(); ;}
    break;

  case 148:
#line 593 "faustparser.y"
    { (yyval.exp) = gGlobal->gRoundPrim->box(); ;}
    break;

  case 149:
#line 595 "faustparser.y"
    { (yyval.exp) = boxReadOnlyTable(); ;}
    break;

  case 150:
#line 596 "faustparser.y"
    { (yyval.exp) = boxWriteReadTable(); ;}
    break;

  case 151:
#line 598 "faustparser.y"
    { (yyval.exp) = boxSelect2(); ;}
    break;

  case 152:
#line 599 "faustparser.y"
    { (yyval.exp) = boxSelect3(); ;}
    break;

  case 153:
#line 601 "faustparser.y"
    { (yyval.exp) = boxAssertBound(); ;}
    break;

  case 154:
#line 602 "faustparser.y"
    { (yyval.exp) = boxLowest(); ;}
    break;

  case 155:
#line 603 "faustparser.y"
    { (yyval.exp) = boxHighest(); ;}
    break;

  case 156:
#line 605 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); setUseProp((yyvsp[(1) - (1)].exp), FAUSTfilename, FAUSTlineno);;}
    break;

  case 157:
#line 606 "faustparser.y"
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[(2) - (2)].exp)),boxSub()); ;}
    break;

  case 158:
#line 608 "faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); ;}
    break;

  case 159:
#line 610 "faustparser.y"
    { (yyval.exp) = buildBoxAbstr((yyvsp[(3) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 160:
#line 616 "faustparser.y"
    { (yyval.exp) = buildBoxModulation((yyvsp[(2) - (5)].exp),(yyvsp[(4) - (5)].exp)); ;}
    break;

  case 161:
#line 618 "faustparser.y"
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 162:
#line 620 "faustparser.y"
    { (yyval.exp) = boxFFun((yyvsp[(1) - (1)].exp)); ;}
    break;

  case 163:
#line 621 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 164:
#line 622 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 165:
#line 623 "faustparser.y"
    { (yyval.exp) = boxComponent((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 166:
#line 624 "faustparser.y"
    { (yyval.exp) = boxLibrary((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 167:
#line 625 "faustparser.y"
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[(3) - (4)].exp))); ;}
    break;

  case 168:
#line 626 "faustparser.y"
    { (yyval.exp) = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); ;}
    break;

  case 169:
#line 627 "faustparser.y"
    { (yyval.exp) = boxRoute((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp), boxPar(boxInt(0),boxInt(0))); ;}
    break;

  case 170:
#line 628 "faustparser.y"
    { (yyval.exp) = boxRoute((yyvsp[(3) - (8)].exp), (yyvsp[(5) - (8)].exp), (yyvsp[(7) - (8)].exp)); ;}
    break;

  case 171:
#line 629 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 172:
#line 630 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 173:
#line 631 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 174:
#line 632 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 175:
#line 633 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 176:
#line 634 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 177:
#line 635 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 178:
#line 636 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 179:
#line 637 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 180:
#line 638 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 181:
#line 639 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 182:
#line 641 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 183:
#line 642 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 184:
#line 643 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 185:
#line 644 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 186:
#line 646 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 187:
#line 647 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 188:
#line 648 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 189:
#line 649 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 190:
#line 650 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 191:
#line 653 "faustparser.y"
    { (yyval.exp) = boxIdent(FAUSTtext); setUseProp((yyval.exp), FAUSTfilename, FAUSTlineno);  ;}
    break;

  case 192:
#line 656 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); setUseProp((yyval.exp), FAUSTfilename, FAUSTlineno);  ;}
    break;

  case 193:
#line 659 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 194:
#line 660 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 195:
#line 663 "faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 196:
#line 664 "faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 197:
#line 665 "faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 198:
#line 666 "faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); ;}
    break;

  case 199:
#line 667 "faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 200:
#line 670 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); ;}
    break;

  case 201:
#line 673 "faustparser.y"
    { (yyval.exp) = unquote(FAUSTtext); ;}
    break;

  case 202:
#line 676 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); ;}
    break;

  case 203:
#line 677 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); ;}
    break;

  case 204:
#line 683 "faustparser.y"
    { (yyval.exp) = boxIPar((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 205:
#line 687 "faustparser.y"
    { (yyval.exp) = boxISeq((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 206:
#line 691 "faustparser.y"
    { (yyval.exp) = boxISum((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 207:
#line 695 "faustparser.y"
    { (yyval.exp) = boxIProd((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 208:
#line 698 "faustparser.y"
    { (yyval.exp) = boxInputs((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 209:
#line 701 "faustparser.y"
    { (yyval.exp) = boxOutputs((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 210:
#line 704 "faustparser.y"
    { (yyval.exp) = boxOndemand((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 211:
#line 707 "faustparser.y"
    { (yyval.exp) = boxUpsampling((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 212:
#line 710 "faustparser.y"
    { (yyval.exp) = boxDownsampling((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 213:
#line 716 "faustparser.y"
    { (yyval.exp) = ffunction((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 214:
#line 720 "faustparser.y"
    { (yyval.exp) = boxFConst((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); ;}
    break;

  case 215:
#line 724 "faustparser.y"
    { (yyval.exp) = boxFVar((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); ;}
    break;

  case 216:
#line 728 "faustparser.y"
    { (yyval.exp) = boxButton((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 217:
#line 731 "faustparser.y"
    { (yyval.exp) = boxCheckbox((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 218:
#line 735 "faustparser.y"
    { (yyval.exp) = boxVSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 219:
#line 738 "faustparser.y"
    { (yyval.exp) = boxHSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 220:
#line 741 "faustparser.y"
    { (yyval.exp) = boxNumEntry((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); ;}
    break;

  case 221:
#line 744 "faustparser.y"
    { (yyval.exp) = boxVGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 222:
#line 747 "faustparser.y"
    { (yyval.exp) = boxHGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 223:
#line 750 "faustparser.y"
    { (yyval.exp) = boxTGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); ;}
    break;

  case 224:
#line 754 "faustparser.y"
    { (yyval.exp) = boxVBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 225:
#line 757 "faustparser.y"
    { (yyval.exp) = boxHBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); ;}
    break;

  case 226:
#line 760 "faustparser.y"
    { (yyval.exp) = boxSoundfile((yyvsp[(3) - (6)].exp),(yyvsp[(5) - (6)].exp)); ;}
    break;

  case 227:
#line 766 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (5)].exp),cons(cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),gGlobal->nil)))), (yyvsp[(4) - (5)].exp))); ;}
    break;

  case 228:
#line 767 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp),cons(cons((yyvsp[(2) - (7)].exp),cons((yyvsp[(4) - (7)].exp),cons((yyvsp[(4) - (7)].exp),cons((yyvsp[(4) - (7)].exp),gGlobal->nil)))), (yyvsp[(6) - (7)].exp))); ;}
    break;

  case 229:
#line 768 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (9)].exp),cons(cons((yyvsp[(2) - (9)].exp),cons((yyvsp[(4) - (9)].exp),cons((yyvsp[(6) - (9)].exp),cons((yyvsp[(6) - (9)].exp),gGlobal->nil)))), (yyvsp[(8) - (9)].exp))); ;}
    break;

  case 230:
#line 769 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (11)].exp),cons(cons((yyvsp[(2) - (11)].exp),cons((yyvsp[(4) - (11)].exp),cons((yyvsp[(6) - (11)].exp),cons((yyvsp[(8) - (11)].exp),gGlobal->nil)))), (yyvsp[(10) - (11)].exp))); ;}
    break;

  case 231:
#line 771 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),gGlobal->nil)))), gGlobal->nil)); ;}
    break;

  case 232:
#line 772 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (6)].exp),cons(cons((yyvsp[(2) - (6)].exp),cons((yyvsp[(4) - (6)].exp),cons((yyvsp[(4) - (6)].exp),cons((yyvsp[(4) - (6)].exp),gGlobal->nil)))), gGlobal->nil)); ;}
    break;

  case 233:
#line 773 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (8)].exp),cons(cons((yyvsp[(2) - (8)].exp),cons((yyvsp[(4) - (8)].exp),cons((yyvsp[(6) - (8)].exp),cons((yyvsp[(6) - (8)].exp),gGlobal->nil)))), gGlobal->nil)); ;}
    break;

  case 234:
#line 774 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (10)].exp),cons(cons((yyvsp[(2) - (10)].exp),cons((yyvsp[(4) - (10)].exp),cons((yyvsp[(6) - (10)].exp),cons((yyvsp[(8) - (10)].exp),gGlobal->nil)))), gGlobal->nil)); ;}
    break;

  case 235:
#line 777 "faustparser.y"
    { (yyval.exp) = tree(FAUSTtext); ;}
    break;

  case 236:
#line 780 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 237:
#line 781 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); ;}
    break;

  case 238:
#line 784 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); ;}
    break;

  case 239:
#line 785 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); ;}
    break;

  case 240:
#line 789 "faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (6)].exp),(yyvsp[(5) - (6)].exp)); ;}
    break;

  case 241:
#line 792 "faustparser.y"
    { (yyval.exp) = tree(0); ;}
    break;

  case 242:
#line 793 "faustparser.y"
    { (yyval.exp) = tree(1); ;}
    break;

  case 243:
#line 796 "faustparser.y"
    { (yyval.exp) = tree(0); ;}
    break;

  case 244:
#line 797 "faustparser.y"
    { (yyval.exp) = tree(1); ;}
    break;

  case 245:
#line 798 "faustparser.y"
    { (yyval.exp) = tree(2); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3476 "faustparser.cpp"
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


#line 801 "faustparser.y"


