/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 5 "parser/faustparser.y"


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


/* Line 371 of yacc.c  */
#line 133 "parser/faustparser.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "faustparser.hpp".  */
#ifndef YY_YY_PARSER_FAUSTPARSER_HPP_INCLUDED
# define YY_YY_PARSER_FAUSTPARSER_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
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
     WAVEFORM = 345,
     IPAR = 346,
     ISEQ = 347,
     ISUM = 348,
     IPROD = 349,
     INPUTS = 350,
     OUTPUTS = 351,
     STRING = 352,
     FSTRING = 353,
     IDENT = 354,
     EXTRA = 355,
     DECLARE = 356,
     CASE = 357,
     ARROW = 358,
     BDOC = 359,
     EDOC = 360,
     BEQN = 361,
     EEQN = 362,
     BDGM = 363,
     EDGM = 364,
     BLST = 365,
     ELST = 366,
     BMETADATA = 367,
     EMETADATA = 368,
     DOCCHAR = 369,
     NOTICE = 370,
     LISTING = 371,
     LSTTRUE = 372,
     LSTFALSE = 373,
     LSTDEPENDENCIES = 374,
     LSTMDOCTAGS = 375,
     LSTDISTRIBUTED = 376,
     LSTEQ = 377,
     LSTQ = 378
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 71 "parser/faustparser.y"

	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;


/* Line 387 of yacc.c  */
#line 307 "parser/faustparser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_PARSER_FAUSTPARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 335 "parser/faustparser.cpp"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
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
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   661

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  124
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  205
/* YYNRULES -- Number of states.  */
#define YYNSTATES  443

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   378

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
     115,   116,   117,   118,   119,   120,   121,   122,   123
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    10,    13,    15,    19,
      21,    23,    26,    29,    32,    35,    41,    46,    48,    52,
      53,    56,    58,    60,    62,    64,    66,    68,    69,    72,
      76,    80,    82,    86,    87,    90,    96,   102,   108,   110,
     112,   116,   124,   129,   132,   134,   136,   140,   146,   150,
     154,   158,   162,   166,   168,   172,   176,   180,   184,   188,
     192,   196,   199,   203,   207,   211,   215,   219,   223,   227,
     231,   235,   239,   243,   247,   252,   257,   259,   261,   263,
     266,   269,   272,   275,   277,   279,   281,   283,   285,   287,
     289,   291,   293,   295,   297,   299,   301,   303,   305,   307,
     309,   311,   313,   315,   317,   319,   321,   323,   325,   327,
     329,   331,   333,   335,   337,   339,   341,   343,   345,   347,
     349,   351,   353,   355,   357,   359,   361,   363,   365,   367,
     369,   371,   373,   375,   378,   382,   391,   396,   398,   400,
     402,   407,   412,   417,   422,   424,   426,   428,   430,   432,
     434,   436,   438,   440,   442,   444,   446,   448,   450,   452,
     454,   456,   458,   460,   464,   468,   472,   476,   480,   482,
     484,   486,   488,   490,   499,   508,   517,   526,   531,   536,
     545,   553,   561,   566,   571,   584,   597,   610,   617,   624,
     631,   640,   649,   655,   663,   673,   678,   685,   694,   696,
     698,   702,   704,   707,   714,   716
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     125,     0,    -1,   126,    -1,    -1,   126,   130,    -1,    -1,
     127,   142,    -1,   129,    -1,   128,     7,   129,    -1,    72,
      -1,    73,    -1,    17,    72,    -1,    17,    73,    -1,    16,
      72,    -1,    16,    73,    -1,    86,    79,   153,    80,    77,
      -1,   101,   149,   152,    77,    -1,   142,    -1,   104,   131,
     105,    -1,    -1,   131,   132,    -1,   133,    -1,   134,    -1,
     135,    -1,   136,    -1,   137,    -1,   141,    -1,    -1,   133,
     114,    -1,   106,   145,   107,    -1,   108,   145,   109,    -1,
     115,    -1,   110,   138,   111,    -1,    -1,   138,   139,    -1,
     119,   122,   123,   140,   123,    -1,   120,   122,   123,   140,
     123,    -1,   121,   122,   123,   140,   123,    -1,   117,    -1,
     118,    -1,   112,   149,   113,    -1,   143,    79,   150,    80,
      85,   145,    77,    -1,   143,    85,   145,    77,    -1,     1,
      77,    -1,   148,    -1,   148,    -1,   144,     7,   148,    -1,
     145,     3,    81,   127,    82,    -1,   145,     7,   145,    -1,
     145,     6,   145,    -1,   145,     5,   145,    -1,   145,     4,
     145,    -1,   145,     8,   145,    -1,   146,    -1,   146,    17,
     146,    -1,   146,    16,   146,    -1,   146,    24,   146,    -1,
     146,    23,   146,    -1,   146,    22,   146,    -1,   146,    25,
     146,    -1,   146,    26,   146,    -1,   146,    27,    -1,   146,
      28,   148,    -1,   146,    21,   146,    -1,   146,    15,   146,
      -1,   146,    20,   146,    -1,   146,    19,   146,    -1,   146,
      18,   146,    -1,   146,    14,   146,    -1,   146,    13,   146,
      -1,   146,    11,   146,    -1,   146,    10,   146,    -1,   146,
      12,   146,    -1,   146,     9,   146,    -1,   146,    79,   150,
      80,    -1,   146,    83,   127,    84,    -1,   147,    -1,    72,
      -1,    73,    -1,    17,    72,    -1,    17,    73,    -1,    16,
      72,    -1,    16,    73,    -1,    75,    -1,    76,    -1,    30,
      -1,    31,    -1,    32,    -1,    33,    -1,    17,    -1,    16,
      -1,    24,    -1,    23,    -1,    22,    -1,    26,    -1,    21,
      -1,    15,    -1,    20,    -1,    19,    -1,    18,    -1,    14,
      -1,    13,    -1,    11,    -1,    10,    -1,    12,    -1,     9,
      -1,    47,    -1,    48,    -1,    49,    -1,    50,    -1,    51,
      -1,    52,    -1,    53,    -1,    54,    -1,    55,    -1,    56,
      -1,    57,    -1,    25,    -1,    58,    -1,    59,    -1,    60,
      -1,    61,    -1,    62,    -1,    63,    -1,    64,    -1,    65,
      -1,    66,    -1,    67,    -1,    68,    -1,    69,    -1,    70,
      -1,    71,    -1,   148,    -1,    16,   148,    -1,    79,   145,
      80,    -1,    74,    79,   144,    80,    28,    79,   145,    80,
      -1,   102,    81,   177,    82,    -1,   161,    -1,   162,    -1,
     163,    -1,    87,    79,   153,    80,    -1,    88,    79,   153,
      80,    -1,    89,    81,   126,    82,    -1,    90,    81,   128,
      82,    -1,   164,    -1,   165,    -1,   166,    -1,   167,    -1,
     168,    -1,   169,    -1,   170,    -1,   171,    -1,   172,    -1,
     173,    -1,   155,    -1,   156,    -1,   157,    -1,   158,    -1,
     159,    -1,   160,    -1,    99,    -1,    99,    -1,   151,    -1,
     150,     7,   151,    -1,   151,     6,   151,    -1,   151,     5,
     151,    -1,   151,     4,   151,    -1,   151,     8,   151,    -1,
     146,    -1,    97,    -1,    97,    -1,    97,    -1,    98,    -1,
      91,    79,   148,     7,   151,     7,   145,    80,    -1,    92,
      79,   148,     7,   151,     7,   145,    80,    -1,    93,    79,
     148,     7,   151,     7,   145,    80,    -1,    94,    79,   148,
       7,   151,     7,   145,    80,    -1,    95,    79,   145,    80,
      -1,    96,    79,   145,    80,    -1,    34,    79,   174,     7,
     154,     7,   152,    80,    -1,    35,    79,   179,   149,     7,
     154,    80,    -1,    36,    79,   179,   149,     7,   154,    80,
      -1,    37,    79,   153,    80,    -1,    38,    79,   153,    80,
      -1,    39,    79,   153,     7,   151,     7,   151,     7,   151,
       7,   151,    80,    -1,    40,    79,   153,     7,   151,     7,
     151,     7,   151,     7,   151,    80,    -1,    41,    79,   153,
       7,   151,     7,   151,     7,   151,     7,   151,    80,    -1,
      42,    79,   153,     7,   145,    80,    -1,    43,    79,   153,
       7,   145,    80,    -1,    44,    79,   153,     7,   145,    80,
      -1,    46,    79,   153,     7,   151,     7,   151,    80,    -1,
      45,    79,   153,     7,   151,     7,   151,    80,    -1,   179,
     175,    79,   176,    80,    -1,   179,   175,    15,   175,    79,
     176,    80,    -1,   179,   175,    15,   175,    15,   175,    79,
     176,    80,    -1,   179,   175,    79,    80,    -1,   179,   175,
      15,   175,    79,    80,    -1,   179,   175,    15,   175,    15,
     175,    79,    80,    -1,    99,    -1,   179,    -1,   176,     7,
     179,    -1,   178,    -1,   177,   178,    -1,    79,   150,    80,
     103,   145,    77,    -1,    32,    -1,    33,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   303,   303,   306,   307,   309,   310,   317,   318,   321,
     322,   323,   324,   325,   326,   330,   331,   332,   333,   336,
     337,   340,   341,   342,   343,   344,   345,   348,   349,   352,
     355,   358,   361,   364,   365,   368,   369,   370,   373,   374,
     377,   380,   381,   382,   385,   388,   389,   392,   393,   394,
     395,   396,   397,   398,   401,   402,   403,   404,   405,   406,
     407,   408,   409,   411,   412,   413,   415,   416,   418,   419,
     420,   421,   422,   423,   425,   426,   428,   431,   432,   434,
     435,   437,   438,   440,   441,   443,   444,   446,   447,   449,
     450,   451,   452,   453,   454,   456,   457,   458,   460,   461,
     463,   464,   465,   466,   467,   468,   470,   472,   473,   474,
     475,   476,   477,   478,   480,   481,   482,   483,   484,   485,
     487,   488,   489,   491,   492,   494,   495,   496,   499,   500,
     502,   503,   505,   506,   508,   509,   512,   514,   515,   516,
     517,   518,   519,   520,   521,   522,   523,   524,   525,   526,
     527,   528,   529,   530,   532,   533,   534,   535,   537,   538,
     543,   546,   551,   552,   555,   556,   557,   558,   559,   562,
     565,   568,   569,   574,   578,   582,   586,   591,   594,   601,
     605,   608,   613,   616,   619,   622,   625,   628,   631,   634,
     638,   641,   648,   649,   650,   652,   653,   654,   657,   660,
     661,   664,   665,   668,   672,   673
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
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
  "COMPONENT", "LIBRARY", "ENVIRONMENT", "WAVEFORM", "IPAR", "ISEQ",
  "ISUM", "IPROD", "INPUTS", "OUTPUTS", "STRING", "FSTRING", "IDENT",
  "EXTRA", "DECLARE", "CASE", "ARROW", "BDOC", "EDOC", "BEQN", "EEQN",
  "BDGM", "EDGM", "BLST", "ELST", "BMETADATA", "EMETADATA", "DOCCHAR",
  "NOTICE", "LISTING", "LSTTRUE", "LSTFALSE", "LSTDEPENDENCIES",
  "LSTMDOCTAGS", "LSTDISTRIBUTED", "LSTEQ", "LSTQ", "$accept", "program",
  "stmtlist", "deflist", "vallist", "number", "statement", "doc",
  "docelem", "doctxt", "doceqn", "docdgm", "docntc", "doclst",
  "lstattrlist", "lstattrdef", "lstattrval", "docmtd", "definition",
  "defname", "params", "expression", "infixexp", "primitive", "ident",
  "name", "arglist", "argument", "string", "uqstring", "fstring", "fpar",
  "fseq", "fsum", "fprod", "finputs", "foutputs", "ffunction", "fconst",
  "fvariable", "button", "checkbox", "vslider", "hslider", "nentry",
  "vgroup", "hgroup", "tgroup", "vbargraph", "hbargraph", "signature",
  "fun", "typelist", "rulelist", "rule", "type", YY_NULL
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
     375,   376,   377,   378
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   124,   125,   126,   126,   127,   127,   128,   128,   129,
     129,   129,   129,   129,   129,   130,   130,   130,   130,   131,
     131,   132,   132,   132,   132,   132,   132,   133,   133,   134,
     135,   136,   137,   138,   138,   139,   139,   139,   140,   140,
     141,   142,   142,   142,   143,   144,   144,   145,   145,   145,
     145,   145,   145,   145,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     148,   149,   150,   150,   151,   151,   151,   151,   151,   152,
     153,   154,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   174,   174,   174,   174,   174,   175,   176,
     176,   177,   177,   178,   179,   179
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     0,     2,     1,     3,     1,
       1,     2,     2,     2,     2,     5,     4,     1,     3,     0,
       2,     1,     1,     1,     1,     1,     1,     0,     2,     3,
       3,     1,     3,     0,     2,     5,     5,     5,     1,     1,
       3,     7,     4,     2,     1,     1,     3,     5,     3,     3,
       3,     3,     3,     1,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     4,     4,     1,     1,     1,     2,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     8,     4,     1,     1,     1,
       4,     4,     4,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     8,     8,     8,     8,     4,     4,     8,
       7,     7,     4,     4,    12,    12,    12,     6,     6,     6,
       8,     8,     5,     7,     9,     4,     6,     8,     1,     1,
       3,     1,     2,     6,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   160,     0,    19,     4,
      17,     0,    44,    43,     0,   161,     0,    27,     0,     0,
     170,     0,   169,     0,    18,     0,     0,    33,     0,    31,
      20,    21,    22,    23,    24,    25,    26,   105,   103,   102,
     104,   101,   100,    96,    90,    89,    99,    98,    97,    95,
      93,    92,    91,   117,    94,    85,    86,    87,    88,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,    77,    78,     0,
      83,    84,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   168,    76,   132,     0,   162,   154,
     155,   156,   157,   158,   159,   137,   138,   139,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,     0,    53,
       0,    16,     0,     0,     0,     0,    28,    81,    82,   133,
      79,    80,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     3,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,     0,     0,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    42,    15,    29,    30,    32,     0,     0,     0,
      34,    40,   204,   205,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    45,
     134,     0,     0,     0,     0,     0,     9,    10,     0,     7,
       0,     0,     0,     0,     0,     0,     0,     0,   201,    73,
      71,    70,    72,    69,    68,    64,    55,    54,    67,    66,
      65,    63,    58,    57,    56,    59,    60,    62,     0,     0,
     163,     0,   166,   165,   164,   167,     5,    51,    50,    49,
      48,    52,     0,     0,     0,     0,   198,     0,     0,     0,
     182,   183,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   140,   141,   142,    13,    14,    11,    12,     0,
     143,     0,     0,     0,     0,   177,   178,     0,   136,   202,
      74,    75,     6,     0,     0,     0,     0,     0,   171,   172,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    46,     0,     8,     0,     0,     0,     0,
       0,    41,    47,    38,    39,     0,     0,     0,     0,     0,
     195,     0,   199,     0,     0,     0,     0,     0,   187,   188,
     189,     0,     0,     0,     0,     0,     0,     0,     0,    35,
      36,    37,     0,     0,     0,     0,   192,   180,   181,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     179,     0,   196,     0,   200,     0,     0,     0,   191,   190,
     135,   173,   174,   175,   176,   203,     0,   193,     0,     0,
       0,   197,     0,     0,     0,     0,   194,     0,     0,     0,
     184,   185,   186
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   279,   248,   249,     9,    17,    30,    31,
      32,    33,    34,    35,   144,   220,   365,    36,    10,    11,
     238,   138,   114,   115,   116,    16,   117,   118,    23,    21,
     340,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     224,   297,   371,   257,   258,   372
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -320
static const yytype_int16 yypact[] =
{
    -320,    31,    20,  -320,   -26,   -15,  -320,    -8,  -320,  -320,
    -320,   171,  -320,  -320,   -13,  -320,    39,   212,   382,   382,
    -320,    33,  -320,    38,  -320,   382,   382,  -320,    -8,  -320,
    -320,     3,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,
    -320,  -320,  -320,  -320,    21,    82,  -320,  -320,  -320,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,    47,
      54,   118,   156,   169,   172,   178,   190,   195,   200,   235,
     237,   244,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,   264,
    -320,  -320,   382,   275,   278,   208,   218,   279,   281,   282,
     283,   284,   301,   224,   476,  -320,  -320,    16,   340,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,   332,   476,
     138,  -320,    11,     5,   437,   268,  -320,  -320,  -320,  -320,
    -320,  -320,   151,   151,   151,   -13,   -13,   -13,   -13,   -13,
     -13,   -13,   -13,   -13,   -13,   192,    30,   -13,   -13,  -320,
     188,   192,   192,   192,   192,   382,   382,   305,   382,   382,
     382,   382,   382,   382,   382,   382,   382,   382,   382,   382,
     382,   382,   382,   382,   382,   382,  -320,   192,   382,  -320,
     382,   243,   382,   382,   382,   382,   260,   382,   382,   382,
     382,   382,  -320,  -320,  -320,  -320,  -320,   288,   289,   337,
    -320,  -320,  -320,  -320,   453,   369,    -8,    -8,   399,   400,
     475,   504,   547,   568,   570,   571,   589,   590,    18,  -320,
    -320,   403,   520,     4,   145,   148,  -320,  -320,    15,  -320,
     592,   594,   631,   632,    36,    42,   382,    13,  -320,   497,
     497,   497,   497,   497,   497,   519,   519,   519,   270,   270,
     270,   270,   270,   270,   270,   276,   236,  -320,    19,    28,
     340,   382,   340,   340,    68,  -320,  -320,   522,   522,    94,
     277,  -320,   517,   518,   521,   228,  -320,    73,   635,   636,
    -320,  -320,   382,   382,   382,   382,   382,   382,   382,   382,
     192,   617,  -320,  -320,  -320,  -320,  -320,  -320,  -320,   188,
    -320,   382,   382,   382,   382,  -320,  -320,    71,  -320,  -320,
    -320,  -320,  -320,   459,    29,   213,   213,   213,  -320,  -320,
     639,   369,   175,   228,   228,   527,   545,   556,    49,    55,
      64,   561,   566,  -320,   569,  -320,   577,   582,   587,   599,
     544,  -320,  -320,  -320,  -320,   526,   528,   529,    39,    74,
    -320,    78,  -320,   573,   574,   382,   382,   382,  -320,  -320,
    -320,   382,   382,   382,   382,   382,   382,   382,   382,  -320,
    -320,  -320,   575,   369,   210,   151,  -320,  -320,  -320,   604,
     609,   614,   126,   241,   134,   142,   220,   226,   233,   502,
    -320,   578,  -320,   102,  -320,   382,   382,   382,  -320,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,   249,  -320,   619,   624,
     629,  -320,   136,   382,   382,   382,  -320,   262,   267,   272,
    -320,  -320,  -320
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -320,  -320,   481,   370,  -320,   339,  -320,  -320,  -320,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,    -3,  -320,  -247,  -320,
    -320,     2,   -19,  -320,    22,   -24,  -133,  -123,   291,   215,
       7,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,
    -320,  -268,  -319,  -320,   404,  -151
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
     139,   225,   226,   227,   145,     4,   139,   139,   206,   207,
     208,   209,   210,   211,   206,   207,   208,   209,   210,   211,
      -2,     4,   319,   200,    12,   310,   200,   142,   143,     4,
       4,     3,   332,   206,   207,   208,   209,   210,   211,   206,
     207,   208,   209,   210,   211,   206,   207,   208,   209,   210,
     211,    13,   206,   207,   208,   209,   210,   211,   206,   207,
     208,   209,   210,   211,    14,   278,   149,   206,   207,   208,
     209,   210,   211,   369,   204,   413,   205,   280,   200,   282,
     283,   284,   285,   139,    20,   395,   314,   332,   341,   393,
       5,    15,   256,   147,   148,   328,   201,   320,   311,   330,
     209,   210,   211,     6,   166,     7,     5,   432,     8,   395,
     240,   362,   331,   140,   215,   141,   325,   146,   214,     6,
       6,     7,   326,   327,     8,   411,   152,     6,     6,   378,
     202,   203,   204,   153,   205,   379,    22,   206,   207,   208,
     209,   210,   211,   395,   380,   206,   207,   208,   209,   210,
     211,   360,   342,   394,   150,   151,   139,   139,   396,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   254,   255,   345,
     346,   347,   427,   222,   223,   351,   352,   239,   139,   139,
     139,   139,   139,   250,   251,   252,   253,   154,   356,   357,
     358,   359,   298,   299,   244,   245,   418,   222,   223,   287,
     288,   289,   290,   291,   420,   213,   436,   315,   316,   277,
     317,   318,   421,   206,   207,   208,   209,   210,   211,   206,
     207,   208,   209,   210,   211,   155,   206,   207,   208,   209,
     210,   211,   222,   223,   414,   202,   203,   204,   156,   205,
      18,   157,   399,   400,   401,   370,    19,   158,   402,   403,
     246,   247,   139,   196,   197,    12,   202,   203,   204,   159,
     205,   202,   203,   204,   160,   205,   202,   203,   204,   161,
     205,   222,   223,   333,   210,   211,   139,   139,   139,   169,
     412,     6,   428,   429,   430,   194,   195,   196,   197,   170,
     422,    12,   195,   196,   197,   177,   423,   348,   349,   350,
     437,   438,   439,   424,   162,   198,   163,    24,    25,   199,
      26,   419,    27,   164,    28,   338,   339,    29,   281,   431,
     363,   364,   353,   366,   367,   206,   207,   208,   209,   210,
     211,   286,   440,   165,   202,   203,   204,   441,   205,   198,
     373,   374,   442,   199,   167,   198,    12,   168,   171,   199,
     172,   173,   174,   175,   139,   139,   139,   139,   139,   139,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     176,   221,   241,   242,   256,   404,   405,   406,   407,   408,
     409,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,   212,
     292,   293,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   294,
     295,   102,   206,   207,   208,   209,   210,   211,   296,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   300,
     301,     6,   302,   312,   113,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   206,   207,   208,   209,   210,
     211,   303,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   207,   208,   209,   210,
     211,   202,   203,   204,   375,   205,   361,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   216,   202,
     203,   204,   376,   205,   304,   198,   217,   218,   219,   199,
     202,   203,   204,   377,   205,   202,   203,   204,   381,   205,
     202,   203,   204,   382,   205,   305,   198,   306,   307,   425,
     199,   202,   203,   204,   384,   205,   202,   203,   204,   385,
     205,   202,   203,   204,   386,   205,   308,   309,   198,   321,
     313,   322,   199,   202,   203,   204,   387,   205,   202,   203,
     204,   415,   205,   202,   203,   204,   416,   205,   202,   203,
     204,   417,   205,   202,   203,   204,   433,   205,   202,   203,
     204,   434,   205,   202,   203,   204,   435,   205,   323,   324,
     335,   336,   343,   344,   337,   354,   368,   388,   383,   389,
     243,   390,   391,   397,   398,   410,   334,   426,   355,   392,
       0,   329
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-320)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      19,   152,   153,   154,    28,     1,    25,    26,     3,     4,
       5,     6,     7,     8,     3,     4,     5,     6,     7,     8,
       0,     1,     7,     7,     2,     7,     7,    25,    26,     1,
       1,     0,   279,     3,     4,     5,     6,     7,     8,     3,
       4,     5,     6,     7,     8,     3,     4,     5,     6,     7,
       8,    77,     3,     4,     5,     6,     7,     8,     3,     4,
       5,     6,     7,     8,    79,   198,    44,     3,     4,     5,
       6,     7,     8,   341,     6,   394,     8,   200,     7,   202,
     203,   204,   205,   102,    97,     7,    82,   334,    15,    15,
      86,    99,    79,    72,    73,    82,    80,    82,    80,    80,
       6,     7,     8,    99,   102,   101,    86,   426,   104,     7,
      80,    82,    84,    80,   109,    77,    80,   114,   107,    99,
      99,   101,    80,   256,   104,   393,    79,    99,    99,    80,
       4,     5,     6,    79,     8,    80,    97,     3,     4,     5,
       6,     7,     8,     7,    80,     3,     4,     5,     6,     7,
       8,    80,    79,    79,    72,    73,   175,   176,    80,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   175,   176,   302,
     303,   304,    80,    32,    33,   308,   309,   165,   207,   208,
     209,   210,   211,   171,   172,   173,   174,    79,   321,   322,
     323,   324,   226,   227,    16,    17,    80,    32,    33,   207,
     208,   209,   210,   211,    80,    77,    80,    72,    73,   197,
      72,    73,    80,     3,     4,     5,     6,     7,     8,     3,
       4,     5,     6,     7,     8,    79,     3,     4,     5,     6,
       7,     8,    32,    33,   395,     4,     5,     6,    79,     8,
      79,    79,   375,   376,   377,    80,    85,    79,   381,   382,
      72,    73,   281,    27,    28,   243,     4,     5,     6,    79,
       8,     4,     5,     6,    79,     8,     4,     5,     6,    79,
       8,    32,    33,   281,     7,     8,   305,   306,   307,    81,
      80,    99,   415,   416,   417,    25,    26,    27,    28,    81,
      80,   279,    26,    27,    28,    81,    80,   305,   306,   307,
     433,   434,   435,    80,    79,    79,    79,   105,   106,    83,
     108,    80,   110,    79,   112,    97,    98,   115,    85,    80,
     117,   118,   310,   336,   337,     3,     4,     5,     6,     7,
       8,    81,    80,    79,     4,     5,     6,    80,     8,    79,
     343,   344,    80,    83,    79,    79,   334,    79,    79,    83,
      79,    79,    79,    79,   383,   384,   385,   386,   387,   388,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
      79,   113,   167,   168,    79,   383,   384,   385,   386,   387,
     388,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    77,
     122,   122,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,   122,
       7,    79,     3,     4,     5,     6,     7,     8,    99,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    80,
      80,    99,     7,    80,   102,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,     3,     4,     5,     6,     7,
       8,     7,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,     4,     5,     6,     7,
       8,     4,     5,     6,     7,     8,    77,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,   111,     4,
       5,     6,     7,     8,     7,    79,   119,   120,   121,    83,
       4,     5,     6,     7,     8,     4,     5,     6,     7,     8,
       4,     5,     6,     7,     8,     7,    79,     7,     7,    77,
      83,     4,     5,     6,     7,     8,     4,     5,     6,     7,
       8,     4,     5,     6,     7,     8,     7,     7,    79,     7,
      80,     7,    83,     4,     5,     6,     7,     8,     4,     5,
       6,     7,     8,     4,     5,     6,     7,     8,     4,     5,
       6,     7,     8,     4,     5,     6,     7,     8,     4,     5,
       6,     7,     8,     4,     5,     6,     7,     8,     7,     7,
     123,   123,     7,     7,   123,    28,     7,   103,    79,   123,
     169,   123,   123,    80,    80,    80,   286,    79,   319,   368,
      -1,   257
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   125,   126,     0,     1,    86,    99,   101,   104,   130,
     142,   143,   148,    77,    79,    99,   149,   131,    79,    85,
      97,   153,    97,   152,   105,   106,   108,   110,   112,   115,
     132,   133,   134,   135,   136,   137,   141,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    79,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,   102,   146,   147,   148,   150,   151,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   145,   146,
      80,    77,   145,   145,   138,   149,   114,    72,    73,   148,
      72,    73,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,   145,    79,    79,    81,
      81,    79,    79,    79,    79,    79,    79,    81,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    79,    83,
       7,    80,     4,     5,     6,     8,     3,     4,     5,     6,
       7,     8,    77,    77,   107,   109,   111,   119,   120,   121,
     139,   113,    32,    33,   174,   179,   179,   179,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   144,   148,
      80,   153,   153,   126,    16,    17,    72,    73,   128,   129,
     148,   148,   148,   148,   145,   145,    79,   177,   178,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   148,   150,   127,
     151,    85,   151,   151,   151,   151,    81,   145,   145,   145,
     145,   145,   122,   122,   122,     7,    99,   175,   149,   149,
      80,    80,     7,     7,     7,     7,     7,     7,     7,     7,
       7,    80,    80,    80,    82,    72,    73,    72,    73,     7,
      82,     7,     7,     7,     7,    80,    80,   150,    82,   178,
      80,    84,   142,   145,   127,   123,   123,   123,    97,    98,
     154,    15,    79,     7,     7,   151,   151,   151,   145,   145,
     145,   151,   151,   148,    28,   129,   151,   151,   151,   151,
      80,    77,    82,   117,   118,   140,   140,   140,     7,   175,
      80,   176,   179,   154,   154,     7,     7,     7,    80,    80,
      80,     7,     7,    79,     7,     7,     7,     7,   103,   123,
     123,   123,   152,    15,    79,     7,    80,    80,    80,   151,
     151,   151,   151,   151,   145,   145,   145,   145,   145,   145,
      80,   175,    80,   176,   179,     7,     7,     7,    80,    80,
      80,    80,    80,    80,    80,    77,    79,    80,   151,   151,
     151,    80,   176,     7,     7,     7,    80,   151,   151,   151,
      80,    80,    80
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

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
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

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

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

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

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

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
/* Line 1787 of yacc.c  */
#line 303 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); gGlobal->gResult = formatDefinitions((yyval.exp)); }
    break;

  case 3:
/* Line 1787 of yacc.c  */
#line 306 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->nil; }
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 307 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 309 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->nil; }
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 310 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 317 "parser/faustparser.y"
    { gGlobal->gWaveForm.push_back((yyvsp[(1) - (1)].exp)); }
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 318 "parser/faustparser.y"
    { gGlobal->gWaveForm.push_back((yyvsp[(3) - (3)].exp)); }
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 321 "parser/faustparser.y"
    { (yyval.exp) = boxInt(atoi(yytext)); }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 322 "parser/faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 323 "parser/faustparser.y"
    { (yyval.exp) = boxInt (atoi(yytext)); }
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 324 "parser/faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); }
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 325 "parser/faustparser.y"
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 326 "parser/faustparser.y"
    { (yyval.exp) = boxReal( -atof(yytext) ); }
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 330 "parser/faustparser.y"
    { (yyval.exp) = importFile((yyvsp[(3) - (5)].exp)); }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 331 "parser/faustparser.y"
    { declareMetadata((yyvsp[(2) - (4)].exp),(yyvsp[(3) - (4)].exp)); (yyval.exp) = gGlobal->nil; }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 332 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 333 "parser/faustparser.y"
    { declareDoc((yyvsp[(2) - (3)].exp)); (yyval.exp) = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 336 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->nil; }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 337 "parser/faustparser.y"
    { (yyval.exp) = cons ((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); }
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 340 "parser/faustparser.y"
    { (yyval.exp) = docTxt((yyvsp[(1) - (1)].cppstr)->c_str()); delete (yyvsp[(1) - (1)].cppstr); }
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 341 "parser/faustparser.y"
    { (yyval.exp) = docEqn((yyvsp[(1) - (1)].exp)); }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 342 "parser/faustparser.y"
    { (yyval.exp) = docDgm((yyvsp[(1) - (1)].exp)); }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 343 "parser/faustparser.y"
    { (yyval.exp) = docNtc(); }
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 344 "parser/faustparser.y"
    { (yyval.exp) = docLst(); }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 345 "parser/faustparser.y"
    { (yyval.exp) = docMtd((yyvsp[(1) - (1)].exp)); }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 348 "parser/faustparser.y"
    { (yyval.cppstr) = new string(); }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 349 "parser/faustparser.y"
    { (yyval.cppstr) = &((yyvsp[(1) - (2)].cppstr)->append(yytext)); }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 352 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 355 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 358 "parser/faustparser.y"
    { }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 361 "parser/faustparser.y"
    { }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 364 "parser/faustparser.y"
    { }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 365 "parser/faustparser.y"
    { }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 368 "parser/faustparser.y"
    { gGlobal->gLstDependenciesSwitch = (yyvsp[(4) - (5)].b); }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 369 "parser/faustparser.y"
    { gGlobal->gStripDocSwitch = (yyvsp[(4) - (5)].b); gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 370 "parser/faustparser.y"
    { gGlobal->gLstDistributedSwitch = (yyvsp[(4) - (5)].b); }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 373 "parser/faustparser.y"
    { (yyval.b) = true; }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 374 "parser/faustparser.y"
    { (yyval.b) = false; }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 377 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 380 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp),cons((yyvsp[(3) - (7)].exp),(yyvsp[(6) - (7)].exp))); }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 381 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp),cons(gGlobal->nil,(yyvsp[(3) - (4)].exp))); }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 382 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->nil; yyerr++; }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 385 "parser/faustparser.y"
    { (yyval.exp)=(yyvsp[(1) - (1)].exp); setDefProp((yyvsp[(1) - (1)].exp), yyfilename, yylineno); }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 388 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); }
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 389 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 392 "parser/faustparser.y"
    { (yyval.exp) = boxWithLocalDef((yyvsp[(1) - (5)].exp),formatDefinitions((yyvsp[(4) - (5)].exp))); }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 393 "parser/faustparser.y"
    { (yyval.exp) = boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 394 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 395 "parser/faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 396 "parser/faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 397 "parser/faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 398 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 401 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAdd)); }
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 402 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigSub)); }
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 403 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigMul)); }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 404 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigDiv)); }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 405 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRem)); }
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 406 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),gGlobal->gPowPrim->box()); }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 407 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigFixDelay)); }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 408 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (2)].exp),boxPrim1(sigDelay1)); }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 409 "parser/faustparser.y"
    { (yyval.exp) = boxAccess((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 411 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigAND)); }
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 412 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigOR)); }
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 413 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigXOR)); }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 415 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLeftShift)); }
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 416 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigRightShift)); }
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 418 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLT)); }
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 419 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigLE)); }
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 420 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGT)); }
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 421 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigGE)); }
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 422 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigEQ)); }
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 423 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)),boxPrim2(sigNE)); }
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 425 "parser/faustparser.y"
    { (yyval.exp) = buildBoxAppl((yyvsp[(1) - (4)].exp),(yyvsp[(3) - (4)].exp)); }
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 426 "parser/faustparser.y"
    { (yyval.exp) = boxModifLocalDef((yyvsp[(1) - (4)].exp),formatDefinitions((yyvsp[(3) - (4)].exp))); }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 428 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 431 "parser/faustparser.y"
    { (yyval.exp) = boxInt(atoi(yytext)); }
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 432 "parser/faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); }
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 434 "parser/faustparser.y"
    { (yyval.exp) = boxInt (atoi(yytext)); }
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 435 "parser/faustparser.y"
    { (yyval.exp) = boxReal(atof(yytext)); }
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 437 "parser/faustparser.y"
    { (yyval.exp) = boxInt ( -atoi(yytext) ); }
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 438 "parser/faustparser.y"
    { (yyval.exp) = boxReal( -atof(yytext) ); }
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 440 "parser/faustparser.y"
    { (yyval.exp) = boxWire(); }
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 441 "parser/faustparser.y"
    { (yyval.exp) = boxCut(); }
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 443 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigDelay1); }
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 444 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigPrefix); }
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 446 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigIntCast); }
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 447 "parser/faustparser.y"
    { (yyval.exp) = boxPrim1(sigFloatCast); }
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 449 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAdd); }
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 450 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigSub); }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 451 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigMul); }
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 452 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigDiv); }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 453 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigRem); }
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 454 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigFixDelay); }
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 456 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAND); }
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 457 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigOR); }
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 458 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigXOR); }
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 460 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLeftShift); }
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 461 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigRightShift); }
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 463 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLT); }
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 464 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigLE); }
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 465 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigGT); }
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 466 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigGE); }
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 467 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigEQ); }
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 468 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigNE); }
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 470 "parser/faustparser.y"
    { (yyval.exp) = boxPrim2(sigAttach); }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 472 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gAcosPrim->box(); }
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 473 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gAsinPrim->box(); }
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 474 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gAtanPrim->box(); }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 475 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gAtan2Prim->box(); }
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 476 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gCosPrim->box(); }
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 477 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gSinPrim->box(); }
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 478 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gTanPrim->box(); }
    break;

  case 114:
/* Line 1787 of yacc.c  */
#line 480 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gExpPrim->box(); }
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 481 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gLogPrim->box(); }
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 482 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gLog10Prim->box(); }
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 483 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gPowPrim->box(); }
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 484 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gPowPrim->box(); }
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 485 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gSqrtPrim->box(); }
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 487 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gAbsPrim->box(); }
    break;

  case 121:
/* Line 1787 of yacc.c  */
#line 488 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gMinPrim->box(); }
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 489 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gMaxPrim->box(); }
    break;

  case 123:
/* Line 1787 of yacc.c  */
#line 491 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gFmodPrim->box(); }
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 492 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gRemainderPrim->box(); }
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 494 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gFloorPrim->box(); }
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 495 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gCeilPrim->box(); }
    break;

  case 127:
/* Line 1787 of yacc.c  */
#line 496 "parser/faustparser.y"
    { (yyval.exp) = gGlobal->gRintPrim->box(); }
    break;

  case 128:
/* Line 1787 of yacc.c  */
#line 499 "parser/faustparser.y"
    { (yyval.exp) = boxPrim3(sigReadOnlyTable); }
    break;

  case 129:
/* Line 1787 of yacc.c  */
#line 500 "parser/faustparser.y"
    { (yyval.exp) = boxPrim5(sigWriteReadTable); }
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 502 "parser/faustparser.y"
    { (yyval.exp) = boxPrim3(sigSelect2); }
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 503 "parser/faustparser.y"
    { (yyval.exp) = boxPrim4(sigSelect3); }
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 505 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 506 "parser/faustparser.y"
    { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[(2) - (2)].exp)),boxPrim2(sigSub)); }
    break;

  case 134:
/* Line 1787 of yacc.c  */
#line 508 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); }
    break;

  case 135:
/* Line 1787 of yacc.c  */
#line 510 "parser/faustparser.y"
    { (yyval.exp) = buildBoxAbstr((yyvsp[(3) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 136:
/* Line 1787 of yacc.c  */
#line 512 "parser/faustparser.y"
    { (yyval.exp) = boxCase(checkRulelist((yyvsp[(3) - (4)].exp))); }
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 514 "parser/faustparser.y"
    { (yyval.exp) = boxFFun((yyvsp[(1) - (1)].exp)); }
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 515 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 516 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 517 "parser/faustparser.y"
    { (yyval.exp) = boxComponent((yyvsp[(3) - (4)].exp)); }
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 518 "parser/faustparser.y"
    { (yyval.exp) = boxLibrary((yyvsp[(3) - (4)].exp)); }
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 519 "parser/faustparser.y"
    { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[(3) - (4)].exp))); }
    break;

  case 143:
/* Line 1787 of yacc.c  */
#line 520 "parser/faustparser.y"
    { (yyval.exp) = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); }
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 521 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 145:
/* Line 1787 of yacc.c  */
#line 522 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 523 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 524 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 148:
/* Line 1787 of yacc.c  */
#line 525 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 526 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 527 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 151:
/* Line 1787 of yacc.c  */
#line 528 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 152:
/* Line 1787 of yacc.c  */
#line 529 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 153:
/* Line 1787 of yacc.c  */
#line 530 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 154:
/* Line 1787 of yacc.c  */
#line 532 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 155:
/* Line 1787 of yacc.c  */
#line 533 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 156:
/* Line 1787 of yacc.c  */
#line 534 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 157:
/* Line 1787 of yacc.c  */
#line 535 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 158:
/* Line 1787 of yacc.c  */
#line 537 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 159:
/* Line 1787 of yacc.c  */
#line 538 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 160:
/* Line 1787 of yacc.c  */
#line 543 "parser/faustparser.y"
    { (yyval.exp) = boxIdent(yytext); }
    break;

  case 161:
/* Line 1787 of yacc.c  */
#line 546 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); }
    break;

  case 162:
/* Line 1787 of yacc.c  */
#line 551 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); }
    break;

  case 163:
/* Line 1787 of yacc.c  */
#line 552 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); }
    break;

  case 164:
/* Line 1787 of yacc.c  */
#line 555 "parser/faustparser.y"
    { (yyval.exp) = boxSeq((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 165:
/* Line 1787 of yacc.c  */
#line 556 "parser/faustparser.y"
    { (yyval.exp) = boxSplit((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 166:
/* Line 1787 of yacc.c  */
#line 557 "parser/faustparser.y"
    { (yyval.exp) = boxMerge((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 167:
/* Line 1787 of yacc.c  */
#line 558 "parser/faustparser.y"
    { (yyval.exp) = boxRec((yyvsp[(1) - (3)].exp),(yyvsp[(3) - (3)].exp)); }
    break;

  case 168:
/* Line 1787 of yacc.c  */
#line 559 "parser/faustparser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 169:
/* Line 1787 of yacc.c  */
#line 562 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); }
    break;

  case 170:
/* Line 1787 of yacc.c  */
#line 565 "parser/faustparser.y"
    { (yyval.exp) = unquote(yytext); }
    break;

  case 171:
/* Line 1787 of yacc.c  */
#line 568 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); }
    break;

  case 172:
/* Line 1787 of yacc.c  */
#line 569 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); }
    break;

  case 173:
/* Line 1787 of yacc.c  */
#line 575 "parser/faustparser.y"
    { (yyval.exp) = boxIPar((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 174:
/* Line 1787 of yacc.c  */
#line 579 "parser/faustparser.y"
    { (yyval.exp) = boxISeq((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 175:
/* Line 1787 of yacc.c  */
#line 583 "parser/faustparser.y"
    { (yyval.exp) = boxISum((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 176:
/* Line 1787 of yacc.c  */
#line 587 "parser/faustparser.y"
    { (yyval.exp) = boxIProd((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 177:
/* Line 1787 of yacc.c  */
#line 591 "parser/faustparser.y"
    { (yyval.exp) = boxInputs((yyvsp[(3) - (4)].exp)); }
    break;

  case 178:
/* Line 1787 of yacc.c  */
#line 594 "parser/faustparser.y"
    { (yyval.exp) = boxOutputs((yyvsp[(3) - (4)].exp)); }
    break;

  case 179:
/* Line 1787 of yacc.c  */
#line 602 "parser/faustparser.y"
    { (yyval.exp) = ffunction((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 180:
/* Line 1787 of yacc.c  */
#line 606 "parser/faustparser.y"
    { (yyval.exp) = boxFConst((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); }
    break;

  case 181:
/* Line 1787 of yacc.c  */
#line 609 "parser/faustparser.y"
    { (yyval.exp) = boxFVar((yyvsp[(3) - (7)].exp),(yyvsp[(4) - (7)].exp),(yyvsp[(6) - (7)].exp)); }
    break;

  case 182:
/* Line 1787 of yacc.c  */
#line 613 "parser/faustparser.y"
    { (yyval.exp) = boxButton((yyvsp[(3) - (4)].exp)); }
    break;

  case 183:
/* Line 1787 of yacc.c  */
#line 616 "parser/faustparser.y"
    { (yyval.exp) = boxCheckbox((yyvsp[(3) - (4)].exp)); }
    break;

  case 184:
/* Line 1787 of yacc.c  */
#line 620 "parser/faustparser.y"
    { (yyval.exp) = boxVSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); }
    break;

  case 185:
/* Line 1787 of yacc.c  */
#line 623 "parser/faustparser.y"
    { (yyval.exp) = boxHSlider((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); }
    break;

  case 186:
/* Line 1787 of yacc.c  */
#line 626 "parser/faustparser.y"
    { (yyval.exp) = boxNumEntry((yyvsp[(3) - (12)].exp),(yyvsp[(5) - (12)].exp),(yyvsp[(7) - (12)].exp),(yyvsp[(9) - (12)].exp),(yyvsp[(11) - (12)].exp)); }
    break;

  case 187:
/* Line 1787 of yacc.c  */
#line 629 "parser/faustparser.y"
    { (yyval.exp) = boxVGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); }
    break;

  case 188:
/* Line 1787 of yacc.c  */
#line 632 "parser/faustparser.y"
    { (yyval.exp) = boxHGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); }
    break;

  case 189:
/* Line 1787 of yacc.c  */
#line 635 "parser/faustparser.y"
    { (yyval.exp) = boxTGroup((yyvsp[(3) - (6)].exp), (yyvsp[(5) - (6)].exp)); }
    break;

  case 190:
/* Line 1787 of yacc.c  */
#line 639 "parser/faustparser.y"
    { (yyval.exp) = boxVBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 191:
/* Line 1787 of yacc.c  */
#line 642 "parser/faustparser.y"
    { (yyval.exp) = boxHBargraph((yyvsp[(3) - (8)].exp),(yyvsp[(5) - (8)].exp),(yyvsp[(7) - (8)].exp)); }
    break;

  case 192:
/* Line 1787 of yacc.c  */
#line 648 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (5)].exp), cons(cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),cons((yyvsp[(2) - (5)].exp),gGlobal->nil))), (yyvsp[(4) - (5)].exp))); }
    break;

  case 193:
/* Line 1787 of yacc.c  */
#line 649 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (7)].exp), cons(cons((yyvsp[(2) - (7)].exp),cons((yyvsp[(4) - (7)].exp),cons((yyvsp[(4) - (7)].exp),gGlobal->nil))), (yyvsp[(6) - (7)].exp))); }
    break;

  case 194:
/* Line 1787 of yacc.c  */
#line 650 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (9)].exp), cons(cons((yyvsp[(2) - (9)].exp),cons((yyvsp[(4) - (9)].exp),cons((yyvsp[(6) - (9)].exp),gGlobal->nil))), (yyvsp[(8) - (9)].exp))); }
    break;

  case 195:
/* Line 1787 of yacc.c  */
#line 652 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (4)].exp), cons(cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),cons((yyvsp[(2) - (4)].exp),gGlobal->nil))), gGlobal->nil)); }
    break;

  case 196:
/* Line 1787 of yacc.c  */
#line 653 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (6)].exp), cons(cons((yyvsp[(2) - (6)].exp),cons((yyvsp[(4) - (6)].exp),cons((yyvsp[(4) - (6)].exp),gGlobal->nil))), gGlobal->nil)); }
    break;

  case 197:
/* Line 1787 of yacc.c  */
#line 654 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (8)].exp), cons(cons((yyvsp[(2) - (8)].exp),cons((yyvsp[(4) - (8)].exp),cons((yyvsp[(6) - (8)].exp),gGlobal->nil))), gGlobal->nil)); }
    break;

  case 198:
/* Line 1787 of yacc.c  */
#line 657 "parser/faustparser.y"
    { (yyval.exp) = tree(yytext); }
    break;

  case 199:
/* Line 1787 of yacc.c  */
#line 660 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); }
    break;

  case 200:
/* Line 1787 of yacc.c  */
#line 661 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(3) - (3)].exp),(yyvsp[(1) - (3)].exp)); }
    break;

  case 201:
/* Line 1787 of yacc.c  */
#line 664 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(1) - (1)].exp),gGlobal->nil); }
    break;

  case 202:
/* Line 1787 of yacc.c  */
#line 665 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (2)].exp),(yyvsp[(1) - (2)].exp)); }
    break;

  case 203:
/* Line 1787 of yacc.c  */
#line 669 "parser/faustparser.y"
    { (yyval.exp) = cons((yyvsp[(2) - (6)].exp),(yyvsp[(5) - (6)].exp)); }
    break;

  case 204:
/* Line 1787 of yacc.c  */
#line 672 "parser/faustparser.y"
    { (yyval.exp) = tree(0); }
    break;

  case 205:
/* Line 1787 of yacc.c  */
#line 673 "parser/faustparser.y"
    { (yyval.exp) = tree(1); }
    break;


/* Line 1787 of yacc.c  */
#line 3207 "parser/faustparser.cpp"
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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


/* Line 2050 of yacc.c  */
#line 676 "parser/faustparser.y"


