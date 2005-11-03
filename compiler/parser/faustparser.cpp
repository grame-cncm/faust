/* A Bison parser, made by GNU Bison 2.0.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

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
     EXTRA = 346
   };
#endif
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




/* Copy the first part of user declarations.  */
#line 4 "parser/faustparser.y"


#include "tree.hh"
#include "xtended.hh"
#include "boxes.hh"
#include "prim2.hh"
#include "signals.hh"
#include "errormsg.hh"

#define YYDEBUG 1
#define YYERROR_VERBOSE 1
#define YYMAXDEPTH	100000

extern char* 		yytext;
extern const char* 	yyfilename;
extern int 			yylineno;
extern int 			yyerr;
extern Tree 		gResult;

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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 52 "parser/faustparser.y"
typedef union YYSTYPE {
	CTree* 	exp;
} YYSTYPE;
/* Line 190 of yacc.c.  */
#line 309 "parser/faustparser.cpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 213 of yacc.c.  */
#line 321 "parser/faustparser.cpp"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
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
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   494

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  36
/* YYNRULES -- Number of rules. */
#define YYNRULES  149
/* YYNRULES -- Number of states. */
#define YYNSTATES  323

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   346

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
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
      85,    86,    87,    88,    89,    90,    91
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    17,    22,    28,    31,
      33,    35,    39,    45,    49,    53,    57,    61,    65,    67,
      71,    75,    79,    83,    87,    91,    94,    98,   102,   106,
     110,   114,   118,   122,   126,   130,   134,   138,   142,   147,
     149,   151,   153,   156,   159,   162,   165,   167,   169,   171,
     173,   175,   177,   179,   181,   183,   185,   187,   189,   191,
     193,   195,   197,   199,   201,   203,   205,   207,   209,   211,
     213,   215,   217,   219,   221,   223,   225,   227,   229,   231,
     233,   235,   237,   239,   241,   243,   245,   247,   249,   251,
     253,   255,   257,   259,   261,   263,   267,   276,   278,   280,
     285,   287,   289,   291,   293,   295,   297,   299,   301,   303,
     305,   307,   309,   311,   313,   315,   317,   319,   323,   327,
     331,   335,   339,   341,   343,   345,   347,   349,   358,   367,
     376,   385,   394,   402,   407,   412,   425,   438,   451,   458,
     465,   472,   481,   490,   496,   501,   503,   505,   509,   511
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      93,     0,    -1,    94,    -1,    -1,    94,    95,    -1,    96,
      77,    97,    78,    81,    98,    75,    -1,    96,    81,    98,
      75,    -1,    82,    77,   106,    78,    75,    -1,     1,    75,
      -1,   101,    -1,   101,    -1,    97,     7,   101,    -1,    98,
       3,    79,    94,    80,    -1,    98,     7,    98,    -1,    98,
       6,    98,    -1,    98,     5,    98,    -1,    98,     4,    98,
      -1,    98,     8,    98,    -1,    99,    -1,    99,    17,    99,
      -1,    99,    16,    99,    -1,    99,    24,    99,    -1,    99,
      23,    99,    -1,    99,    22,    99,    -1,    99,    25,    99,
      -1,    99,    26,    -1,    99,    27,   101,    -1,    99,    21,
      99,    -1,    99,    15,    99,    -1,    99,    20,    99,    -1,
      99,    19,    99,    -1,    99,    18,    99,    -1,    99,    14,
      99,    -1,    99,    13,    99,    -1,    99,    11,    99,    -1,
      99,    10,    99,    -1,    99,    12,    99,    -1,    99,     9,
      99,    -1,    99,    77,   103,    78,    -1,   100,    -1,    70,
      -1,    71,    -1,    17,    70,    -1,    17,    71,    -1,    16,
      70,    -1,    16,    71,    -1,    73,    -1,    74,    -1,    29,
      -1,    30,    -1,    31,    -1,    32,    -1,    17,    -1,    16,
      -1,    24,    -1,    23,    -1,    22,    -1,    25,    -1,    21,
      -1,    15,    -1,    20,    -1,    19,    -1,    18,    -1,    14,
      -1,    13,    -1,    11,    -1,    10,    -1,    12,    -1,     9,
      -1,    45,    -1,    46,    -1,    47,    -1,    48,    -1,    49,
      -1,    50,    -1,    51,    -1,    52,    -1,    53,    -1,    54,
      -1,    55,    -1,    56,    -1,    57,    -1,    58,    -1,    59,
      -1,    60,    -1,    61,    -1,    62,    -1,    63,    -1,    64,
      -1,    65,    -1,    66,    -1,    67,    -1,    68,    -1,    69,
      -1,   101,    -1,    77,    98,    78,    -1,    72,    77,    97,
      78,    27,    77,    98,    78,    -1,   112,    -1,   113,    -1,
      83,    77,   106,    78,    -1,   114,    -1,   115,    -1,   116,
      -1,   117,    -1,   118,    -1,   119,    -1,   120,    -1,   121,
      -1,   122,    -1,   123,    -1,   108,    -1,   109,    -1,   110,
      -1,   111,    -1,    90,    -1,    90,    -1,   104,    -1,   103,
       7,   104,    -1,   104,     6,   104,    -1,   104,     5,   104,
      -1,   104,     4,   104,    -1,   104,     8,   104,    -1,    99,
      -1,    88,    -1,    88,    -1,    88,    -1,    89,    -1,    84,
      77,   101,     7,   104,     7,    98,    78,    -1,    85,    77,
     101,     7,   104,     7,    98,    78,    -1,    86,    77,   101,
       7,   104,     7,    98,    78,    -1,    87,    77,   101,     7,
     104,     7,    98,    78,    -1,    33,    77,   124,     7,   107,
       7,   105,    78,    -1,    34,    77,   127,   102,     7,   107,
      78,    -1,    35,    77,   105,    78,    -1,    36,    77,   105,
      78,    -1,    37,    77,   105,     7,   104,     7,   104,     7,
     104,     7,   104,    78,    -1,    38,    77,   105,     7,   104,
       7,   104,     7,   104,     7,   104,    78,    -1,    39,    77,
     105,     7,   104,     7,   104,     7,   104,     7,   104,    78,
      -1,    40,    77,   105,     7,    98,    78,    -1,    41,    77,
     105,     7,    98,    78,    -1,    42,    77,   105,     7,    98,
      78,    -1,    44,    77,   105,     7,   104,     7,   104,    78,
      -1,    43,    77,   105,     7,   104,     7,   104,    78,    -1,
     127,   125,    77,   126,    78,    -1,   127,   125,    77,    78,
      -1,    90,    -1,   127,    -1,   126,     7,   127,    -1,    31,
      -1,    32,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   219,   219,   222,   223,   226,   227,   228,   229,   232,
     235,   236,   239,   240,   241,   242,   243,   244,   245,   248,
     249,   250,   251,   252,   253,   254,   255,   257,   258,   259,
     261,   262,   264,   265,   266,   267,   268,   269,   271,   273,
     276,   277,   279,   280,   282,   283,   285,   286,   288,   289,
     291,   292,   294,   295,   296,   297,   298,   299,   301,   302,
     303,   305,   306,   308,   309,   310,   311,   312,   313,   315,
     317,   318,   319,   320,   321,   322,   323,   325,   326,   327,
     328,   329,   331,   332,   333,   335,   336,   338,   339,   340,
     343,   344,   346,   347,   349,   351,   352,   354,   355,   356,
     358,   359,   360,   361,   362,   363,   364,   365,   366,   367,
     369,   370,   371,   372,   376,   379,   384,   385,   388,   389,
     390,   391,   392,   395,   398,   401,   402,   407,   411,   415,
     419,   426,   430,   435,   438,   441,   444,   447,   450,   453,
     456,   460,   463,   468,   469,   472,   475,   476,   479,   480
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
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
  "FSTRING", "IDENT", "EXTRA", "$accept", "program", "eqlist", "equation",
  "eqname", "params", "diagram", "expression", "primitive", "ident",
  "name", "arglist", "argument", "string", "uqstring", "fstring", "fpar",
  "fseq", "fsum", "fprod", "ffunction", "fconst", "button", "checkbox",
  "vslider", "hslider", "nentry", "vgroup", "hgroup", "tgroup",
  "vbargraph", "hbargraph", "signature", "fun", "typelist", "type", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
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
     345,   346
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    92,    93,    94,    94,    95,    95,    95,    95,    96,
      97,    97,    98,    98,    98,    98,    98,    98,    98,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   101,   102,   103,   103,   104,   104,
     104,   104,   104,   105,   106,   107,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   124,   125,   126,   126,   127,   127
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     0,     2,     7,     4,     5,     2,     1,
       1,     3,     5,     3,     3,     3,     3,     3,     1,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     4,     1,
       1,     1,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     8,     1,     1,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     1,     1,     1,     1,     1,     8,     8,     8,
       8,     8,     7,     4,     4,    12,    12,    12,     6,     6,
       6,     8,     8,     5,     4,     1,     1,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       3,     0,     0,     1,     0,     0,   114,     4,     0,     9,
       8,     0,     0,     0,   124,     0,     0,    10,    68,    66,
      65,    67,    64,    63,    59,    53,    52,    62,    61,    60,
      58,    56,    55,    54,    57,    48,    49,    50,    51,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    40,    41,     0,    46,
      47,     0,     0,     0,     0,     0,     0,     0,    18,    39,
      94,   110,   111,   112,   113,    97,    98,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,     0,     0,     0,
      44,    45,    42,    43,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       7,    11,     0,   148,   149,     0,     0,     0,   123,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      95,     0,     0,     0,     0,     0,     3,    16,    15,    14,
      13,    17,    37,    35,    34,    36,    33,    32,    28,    20,
      19,    31,    30,    29,    27,    23,    22,    21,    24,    26,
     122,     0,   116,     0,     0,   145,     0,   115,     0,   133,
     134,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      99,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,     0,     5,   125,   126,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    12,   117,   120,   119,   118,   121,     0,   144,     0,
     146,     0,     0,     0,     0,   138,   139,   140,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   143,   132,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   131,
     147,     0,     0,     0,   142,   141,    96,   127,   128,   129,
     130,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     135,   136,   137
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     1,     2,     7,     8,    16,    87,   210,    89,    90,
     218,   211,   212,   169,    15,   245,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   165,   216,   269,   166
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -208
static const short int yypact[] =
{
    -208,    23,     1,  -208,   -47,   -27,  -208,  -208,    -7,  -208,
    -208,   -58,   -26,   264,  -208,    -5,    28,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,    11,    34,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,    35,
      43,    79,    85,   114,   130,   131,   132,   133,   137,   144,
     145,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,   146,  -208,
    -208,   264,   165,   166,   180,   181,   215,   364,   371,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,   149,   -26,    17,
    -208,  -208,  -208,  -208,    61,    61,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   -26,    38,   -58,   -26,
     -26,   -26,   -26,   260,   264,   264,   264,   264,   264,  -208,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,  -208,   -26,   264,
    -208,  -208,   264,  -208,  -208,   252,   250,   255,  -208,   274,
     275,   372,   405,   406,   407,   408,   420,   421,   422,    40,
    -208,   359,   431,   439,   440,   452,  -208,    55,    55,   157,
     474,  -208,   384,   384,   384,   384,   384,   384,   214,   214,
     214,    -8,    -8,    -8,    -8,    -8,    -8,    -8,    25,  -208,
     371,    41,   109,   370,    94,  -208,   383,  -208,   476,  -208,
    -208,   264,   264,   264,   264,   264,   264,   264,   264,   457,
    -208,   264,   264,   264,   264,    21,   264,  -208,   264,   264,
     264,   264,  -208,  -208,  -208,   478,    22,    94,   193,   222,
     242,    72,    82,   167,   248,   257,   409,   413,   418,   427,
     436,  -208,   109,    91,    91,   479,  -208,   156,  -208,    48,
    -208,   410,   264,   264,   264,  -208,  -208,  -208,   264,   264,
     264,   264,   264,   264,   264,   411,    61,  -208,  -208,   445,
     450,   458,    32,   147,   173,   182,   212,   352,   358,  -208,
    -208,   264,   264,   264,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,   463,   468,   473,   264,   264,   264,   153,   188,   338,
    -208,  -208,  -208
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -208,  -208,   304,  -208,  -208,   365,   -78,   -13,  -208,    37,
    -208,  -208,  -207,  -113,   366,   245,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -102
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const short int yytable[] =
{
      88,    -2,     4,   127,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   167,   248,   249,   250,   156,   157,   158,
     254,   255,     4,     3,   257,   258,   259,   260,    10,   262,
      14,   263,   264,   265,   266,   108,   238,   239,   240,     9,
     241,   133,   134,   135,   136,   137,   138,   108,   236,    17,
      11,   157,   158,   163,   164,   286,   187,   188,   189,   190,
     191,   136,   137,   138,     6,   289,   290,   291,    88,   159,
      12,   292,   293,   107,    13,   133,   134,   135,   136,   137,
     138,   110,   111,     5,   213,   133,   134,   135,   136,   137,
     138,     6,   163,   164,   311,   312,   313,   240,   162,   241,
     268,   261,   159,     5,   112,   113,   109,   317,   318,   319,
     304,     6,   114,   238,   239,   240,   180,   241,   229,   237,
     115,    88,    88,    88,    88,    88,   287,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   270,   161,   251,   252,   253,    88,
     275,   238,   239,   240,   285,   241,   116,   238,   239,   240,
     276,   241,   117,    17,   137,   138,   182,   183,   184,   185,
     133,   134,   135,   136,   137,   138,   133,   134,   135,   136,
     137,   138,   243,   244,   300,   133,   134,   135,   136,   137,
     138,   118,   238,   239,   240,   209,   241,   238,   239,   240,
     272,   241,   294,   295,   296,   297,   298,   119,   120,   121,
     122,    88,    88,    88,   123,   133,   134,   135,   136,   137,
     138,   124,   125,   126,   160,   305,   238,   239,   240,   273,
     241,   320,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   128,   129,   168,   277,   238,   239,   240,   274,
     241,   306,   238,   239,   240,   278,   241,   130,   131,   214,
     307,   238,   239,   240,   279,   241,   321,    88,    88,    88,
      88,    88,     9,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
     308,   159,   132,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,   186,
     215,    81,   238,   239,   240,   217,   241,    82,    83,    84,
      85,    86,   219,   220,     6,   133,   134,   135,   136,   137,
     138,   133,   134,   135,   136,   137,   138,   133,   134,   135,
     136,   137,   138,   133,   134,   135,   136,   137,   138,   221,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   222,   223,   224,   225,   322,   238,   239,   240,
     281,   241,   238,   239,   240,   282,   241,   226,   227,   228,
     309,   238,   239,   240,   283,   241,   310,   230,   231,   139,
     238,   239,   240,   284,   241,   242,   232,   233,   159,   238,
     239,   240,   301,   241,   238,   239,   240,   302,   241,   234,
     246,   159,   238,   239,   240,   303,   241,   238,   239,   240,
     314,   241,   238,   239,   240,   315,   241,   238,   239,   240,
     316,   241,   138,   247,   256,   267,   280,   241,   288,   299,
     235,   179,   271,     0,   181
};

static const short int yycheck[] =
{
      13,     0,     1,    81,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   115,   221,   222,   223,    25,    26,    27,
     227,   228,     1,     0,   231,   232,   233,   234,    75,   236,
      88,   238,   239,   240,   241,     7,     4,     5,     6,     2,
       8,     3,     4,     5,     6,     7,     8,     7,     7,    12,
      77,    26,    27,    31,    32,     7,   134,   135,   136,   137,
     138,     6,     7,     8,    90,   272,   273,   274,    81,    77,
      77,   278,   279,    78,    81,     3,     4,     5,     6,     7,
       8,    70,    71,    82,   162,     3,     4,     5,     6,     7,
       8,    90,    31,    32,   301,   302,   303,     6,    81,     8,
      78,    80,    77,    82,    70,    71,    78,   314,   315,   316,
      78,    90,    77,     4,     5,     6,    78,     8,    78,    78,
      77,   134,   135,   136,   137,   138,    78,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   246,   108,   224,   225,   226,   162,
      78,     4,     5,     6,   267,     8,    77,     4,     5,     6,
      78,     8,    77,   126,     7,     8,   129,   130,   131,   132,
       3,     4,     5,     6,     7,     8,     3,     4,     5,     6,
       7,     8,    88,    89,   286,     3,     4,     5,     6,     7,
       8,    77,     4,     5,     6,   158,     8,     4,     5,     6,
       7,     8,   280,   281,   282,   283,   284,    77,    77,    77,
      77,   224,   225,   226,    77,     3,     4,     5,     6,     7,
       8,    77,    77,    77,    75,    78,     4,     5,     6,     7,
       8,    78,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    77,    77,    88,    78,     4,     5,     6,     7,
       8,    78,     4,     5,     6,     7,     8,    77,    77,     7,
      78,     4,     5,     6,     7,     8,    78,   280,   281,   282,
     283,   284,   235,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      78,    77,    77,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    79,
      90,    77,     4,     5,     6,    90,     8,    83,    84,    85,
      86,    87,    78,    78,    90,     3,     4,     5,     6,     7,
       8,     3,     4,     5,     6,     7,     8,     3,     4,     5,
       6,     7,     8,     3,     4,     5,     6,     7,     8,     7,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,     7,     7,     7,     7,    78,     4,     5,     6,
       7,     8,     4,     5,     6,     7,     8,     7,     7,     7,
      78,     4,     5,     6,     7,     8,    78,    78,     7,    75,
       4,     5,     6,     7,     8,    75,     7,     7,    77,     4,
       5,     6,     7,     8,     4,     5,     6,     7,     8,     7,
      77,    77,     4,     5,     6,     7,     8,     4,     5,     6,
       7,     8,     4,     5,     6,     7,     8,     4,     5,     6,
       7,     8,     8,     7,    27,     7,    77,     8,    78,    78,
     186,   126,   247,    -1,   128
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    93,    94,     0,     1,    82,    90,    95,    96,   101,
      75,    77,    77,    81,    88,   106,    97,   101,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    77,    83,    84,    85,    86,    87,    98,    99,   100,
     101,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,    78,     7,    78,
      70,    71,    70,    71,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    98,    77,    77,
      77,    77,    77,     3,     4,     5,     6,     7,     8,    75,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    77,
      75,   101,    81,    31,    32,   124,   127,   127,    88,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,    97,
      78,   106,   101,   101,   101,   101,    79,    98,    98,    98,
      98,    98,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,   101,
      99,   103,   104,    98,     7,    90,   125,    90,   102,    78,
      78,     7,     7,     7,     7,     7,     7,     7,     7,    78,
      78,     7,     7,     7,     7,    94,     7,    78,     4,     5,
       6,     8,    75,    88,    89,   107,    77,     7,   104,   104,
     104,    98,    98,    98,   104,   104,    27,   104,   104,   104,
     104,    80,   104,   104,   104,   104,   104,     7,    78,   126,
     127,   107,     7,     7,     7,    78,    78,    78,     7,     7,
      77,     7,     7,     7,     7,   105,     7,    78,    78,   104,
     104,   104,   104,   104,    98,    98,    98,    98,    98,    78,
     127,     7,     7,     7,    78,    78,    78,    78,    78,    78,
      78,   104,   104,   104,     7,     7,     7,   104,   104,   104,
      78,    78,    78
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

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
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
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
    while (0)
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
} while (0)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
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
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

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
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
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
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  register short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

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


  yyvsp[0] = yylval;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
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

/* Do appropriate processing given the current state.  */
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

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

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
#line 219 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp); gResult = (yyval.exp); ;}
    break;

  case 3:
#line 222 "parser/faustparser.y"
    {(yyval.exp) = nil; ;}
    break;

  case 4:
#line 223 "parser/faustparser.y"
    {(yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); ;}
    break;

  case 5:
#line 226 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[-6].exp),buildBoxAbstr((yyvsp[-4].exp),(yyvsp[-1].exp))); ;}
    break;

  case 6:
#line 227 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[-3].exp),(yyvsp[-1].exp)); ;}
    break;

  case 7:
#line 228 "parser/faustparser.y"
    {(yyval.exp) = importFile((yyvsp[-2].exp)); ;}
    break;

  case 8:
#line 229 "parser/faustparser.y"
    {(yyval.exp) = nil; yyerr++;;}
    break;

  case 9:
#line 232 "parser/faustparser.y"
    {(yyval.exp)=(yyvsp[0].exp); setDefProp((yyvsp[0].exp), yyfilename, yylineno); ;}
    break;

  case 10:
#line 235 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[0].exp),nil); ;}
    break;

  case 11:
#line 236 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); ;}
    break;

  case 12:
#line 239 "parser/faustparser.y"
    {(yyval.exp) = boxWithLocalDef((yyvsp[-4].exp),(yyvsp[-1].exp)); ;}
    break;

  case 13:
#line 240 "parser/faustparser.y"
    {(yyval.exp) = boxPar((yyvsp[-2].exp),(yyvsp[0].exp));;}
    break;

  case 14:
#line 241 "parser/faustparser.y"
    {(yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp));;}
    break;

  case 15:
#line 242 "parser/faustparser.y"
    {(yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp));;}
    break;

  case 16:
#line 243 "parser/faustparser.y"
    {(yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp));;}
    break;

  case 17:
#line 244 "parser/faustparser.y"
    {(yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp));;}
    break;

  case 18:
#line 245 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp); ;}
    break;

  case 19:
#line 248 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAdd)); ;}
    break;

  case 20:
#line 249 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigSub)); ;}
    break;

  case 21:
#line 250 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigMul)); ;}
    break;

  case 22:
#line 251 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigDiv)); ;}
    break;

  case 23:
#line 252 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRem)); ;}
    break;

  case 24:
#line 253 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigFixDelay)); ;}
    break;

  case 25:
#line 254 "parser/faustparser.y"
    {(yyval.exp) = boxSeq((yyvsp[-1].exp),boxPrim1(sigDelay1)); ;}
    break;

  case 26:
#line 255 "parser/faustparser.y"
    {(yyval.exp) = boxAccess((yyvsp[-2].exp),(yyvsp[0].exp)); ;}
    break;

  case 27:
#line 257 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAND)); ;}
    break;

  case 28:
#line 258 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigOR)); ;}
    break;

  case 29:
#line 259 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigXOR)); ;}
    break;

  case 30:
#line 261 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLeftShift)); ;}
    break;

  case 31:
#line 262 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRightShift)); ;}
    break;

  case 32:
#line 264 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLT)); ;}
    break;

  case 33:
#line 265 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLE)); ;}
    break;

  case 34:
#line 266 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGT)); ;}
    break;

  case 35:
#line 267 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGE)); ;}
    break;

  case 36:
#line 268 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigEQ)); ;}
    break;

  case 37:
#line 269 "parser/faustparser.y"
    {(yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigNE)); ;}
    break;

  case 38:
#line 271 "parser/faustparser.y"
    {(yyval.exp) = buildBoxAppl((yyvsp[-3].exp),(yyvsp[-1].exp)); ;}
    break;

  case 39:
#line 273 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 40:
#line 276 "parser/faustparser.y"
    {(yyval.exp) = boxInt(atoi(yytext));;}
    break;

  case 41:
#line 277 "parser/faustparser.y"
    {(yyval.exp) = boxReal(atof(yytext));;}
    break;

  case 42:
#line 279 "parser/faustparser.y"
    {(yyval.exp) = boxInt(atoi(yytext));;}
    break;

  case 43:
#line 280 "parser/faustparser.y"
    {(yyval.exp) = boxReal(atof(yytext));;}
    break;

  case 44:
#line 282 "parser/faustparser.y"
    {(yyval.exp) = boxInt(0 - atoi(yytext));;}
    break;

  case 45:
#line 283 "parser/faustparser.y"
    {(yyval.exp) = boxReal(0.0 - atof(yytext));;}
    break;

  case 46:
#line 285 "parser/faustparser.y"
    {(yyval.exp) = boxWire();;}
    break;

  case 47:
#line 286 "parser/faustparser.y"
    {(yyval.exp) = boxCut();;}
    break;

  case 48:
#line 288 "parser/faustparser.y"
    {(yyval.exp) = boxPrim1(sigDelay1);;}
    break;

  case 49:
#line 289 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigPrefix);;}
    break;

  case 50:
#line 291 "parser/faustparser.y"
    {(yyval.exp) = boxPrim1(sigIntCast);;}
    break;

  case 51:
#line 292 "parser/faustparser.y"
    {(yyval.exp) = boxPrim1(sigFloatCast);;}
    break;

  case 52:
#line 294 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigAdd);;}
    break;

  case 53:
#line 295 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigSub);;}
    break;

  case 54:
#line 296 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigMul);;}
    break;

  case 55:
#line 297 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigDiv);;}
    break;

  case 56:
#line 298 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigRem);;}
    break;

  case 57:
#line 299 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigFixDelay);;}
    break;

  case 58:
#line 301 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigAND);;}
    break;

  case 59:
#line 302 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigOR);;}
    break;

  case 60:
#line 303 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigXOR);;}
    break;

  case 61:
#line 305 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigLeftShift);;}
    break;

  case 62:
#line 306 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigRightShift);;}
    break;

  case 63:
#line 308 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigLT);;}
    break;

  case 64:
#line 309 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigLE);;}
    break;

  case 65:
#line 310 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigGT);;}
    break;

  case 66:
#line 311 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigGE);;}
    break;

  case 67:
#line 312 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigEQ);;}
    break;

  case 68:
#line 313 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigNE);;}
    break;

  case 69:
#line 315 "parser/faustparser.y"
    {(yyval.exp) = boxPrim2(sigAttach);;}
    break;

  case 70:
#line 317 "parser/faustparser.y"
    {(yyval.exp) = gAcosPrim->box(); ;}
    break;

  case 71:
#line 318 "parser/faustparser.y"
    {(yyval.exp) = gAsinPrim->box(); ;}
    break;

  case 72:
#line 319 "parser/faustparser.y"
    {(yyval.exp) = gAtanPrim->box(); ;}
    break;

  case 73:
#line 320 "parser/faustparser.y"
    {(yyval.exp) = gAtan2Prim->box(); ;}
    break;

  case 74:
#line 321 "parser/faustparser.y"
    {(yyval.exp) = gCosPrim->box(); ;}
    break;

  case 75:
#line 322 "parser/faustparser.y"
    {(yyval.exp) = gSinPrim->box(); ;}
    break;

  case 76:
#line 323 "parser/faustparser.y"
    {(yyval.exp) = gTanPrim->box(); ;}
    break;

  case 77:
#line 325 "parser/faustparser.y"
    {(yyval.exp) = gExpPrim->box(); ;}
    break;

  case 78:
#line 326 "parser/faustparser.y"
    {(yyval.exp) = gLogPrim->box(); ;}
    break;

  case 79:
#line 327 "parser/faustparser.y"
    {(yyval.exp) = gLog10Prim->box(); ;}
    break;

  case 80:
#line 328 "parser/faustparser.y"
    {(yyval.exp) = gPowPrim->box(); ;}
    break;

  case 81:
#line 329 "parser/faustparser.y"
    {(yyval.exp) = gSqrtPrim->box(); ;}
    break;

  case 82:
#line 331 "parser/faustparser.y"
    {(yyval.exp) = gAbsPrim->box(); ;}
    break;

  case 83:
#line 332 "parser/faustparser.y"
    {(yyval.exp) = gMinPrim->box(); ;}
    break;

  case 84:
#line 333 "parser/faustparser.y"
    {(yyval.exp) = gMaxPrim->box(); ;}
    break;

  case 85:
#line 335 "parser/faustparser.y"
    {(yyval.exp) = gFmodPrim->box(); ;}
    break;

  case 86:
#line 336 "parser/faustparser.y"
    {(yyval.exp) = gRemainderPrim->box(); ;}
    break;

  case 87:
#line 338 "parser/faustparser.y"
    {(yyval.exp) = gFloorPrim->box(); ;}
    break;

  case 88:
#line 339 "parser/faustparser.y"
    {(yyval.exp) = gCeilPrim->box(); ;}
    break;

  case 89:
#line 340 "parser/faustparser.y"
    {(yyval.exp) = gRintPrim->box(); ;}
    break;

  case 90:
#line 343 "parser/faustparser.y"
    {(yyval.exp) = boxPrim3(sigReadOnlyTable);;}
    break;

  case 91:
#line 344 "parser/faustparser.y"
    {(yyval.exp) = boxPrim5(sigWriteReadTable);;}
    break;

  case 92:
#line 346 "parser/faustparser.y"
    {(yyval.exp) = boxPrim3(sigSelect2);;}
    break;

  case 93:
#line 347 "parser/faustparser.y"
    {(yyval.exp) = boxPrim4(sigSelect3);;}
    break;

  case 94:
#line 349 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 95:
#line 351 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[-1].exp);;}
    break;

  case 96:
#line 353 "parser/faustparser.y"
    {(yyval.exp) = buildBoxAbstr((yyvsp[-5].exp),(yyvsp[-1].exp));;}
    break;

  case 97:
#line 354 "parser/faustparser.y"
    {(yyval.exp) = boxFFun((yyvsp[0].exp)); ;}
    break;

  case 98:
#line 355 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 99:
#line 356 "parser/faustparser.y"
    {(yyval.exp) = boxComponent((yyvsp[-1].exp)); ;}
    break;

  case 100:
#line 358 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 101:
#line 359 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 102:
#line 360 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 103:
#line 361 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 104:
#line 362 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 105:
#line 363 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 106:
#line 364 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 107:
#line 365 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 108:
#line 366 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 109:
#line 367 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 110:
#line 369 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 111:
#line 370 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 112:
#line 371 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 113:
#line 372 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 114:
#line 376 "parser/faustparser.y"
    {(yyval.exp) = boxIdent(yytext);;}
    break;

  case 115:
#line 379 "parser/faustparser.y"
    {(yyval.exp) = tree(yytext);;}
    break;

  case 116:
#line 384 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[0].exp),nil); ;}
    break;

  case 117:
#line 385 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); ;}
    break;

  case 118:
#line 388 "parser/faustparser.y"
    {(yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp));;}
    break;

  case 119:
#line 389 "parser/faustparser.y"
    {(yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp));;}
    break;

  case 120:
#line 390 "parser/faustparser.y"
    {(yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp));;}
    break;

  case 121:
#line 391 "parser/faustparser.y"
    {(yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp));;}
    break;

  case 122:
#line 392 "parser/faustparser.y"
    {(yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 123:
#line 395 "parser/faustparser.y"
    {(yyval.exp) = tree(yytext); ;}
    break;

  case 124:
#line 398 "parser/faustparser.y"
    {(yyval.exp) = unquote(yytext); ;}
    break;

  case 125:
#line 401 "parser/faustparser.y"
    {(yyval.exp) = tree(yytext); ;}
    break;

  case 126:
#line 402 "parser/faustparser.y"
    {(yyval.exp) = tree(yytext); ;}
    break;

  case 127:
#line 408 "parser/faustparser.y"
    {(yyval.exp) = boxIPar((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp));;}
    break;

  case 128:
#line 412 "parser/faustparser.y"
    {(yyval.exp) = boxISeq((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp));;}
    break;

  case 129:
#line 416 "parser/faustparser.y"
    {(yyval.exp) = boxISum((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp));;}
    break;

  case 130:
#line 420 "parser/faustparser.y"
    {(yyval.exp) = boxIProd((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp));;}
    break;

  case 131:
#line 427 "parser/faustparser.y"
    {(yyval.exp) = ffunction((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp));;}
    break;

  case 132:
#line 431 "parser/faustparser.y"
    {(yyval.exp) = boxFConst((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp));;}
    break;

  case 133:
#line 435 "parser/faustparser.y"
    {(yyval.exp) = boxButton((yyvsp[-1].exp)); ;}
    break;

  case 134:
#line 438 "parser/faustparser.y"
    {(yyval.exp) = boxCheckbox((yyvsp[-1].exp)); ;}
    break;

  case 135:
#line 442 "parser/faustparser.y"
    {(yyval.exp) = boxVSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); ;}
    break;

  case 136:
#line 445 "parser/faustparser.y"
    {(yyval.exp) = boxHSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); ;}
    break;

  case 137:
#line 448 "parser/faustparser.y"
    {(yyval.exp) = boxNumEntry((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); ;}
    break;

  case 138:
#line 451 "parser/faustparser.y"
    {(yyval.exp) = boxVGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); ;}
    break;

  case 139:
#line 454 "parser/faustparser.y"
    {(yyval.exp) = boxHGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); ;}
    break;

  case 140:
#line 457 "parser/faustparser.y"
    {(yyval.exp) = boxTGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); ;}
    break;

  case 141:
#line 461 "parser/faustparser.y"
    {(yyval.exp) = boxVBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); ;}
    break;

  case 142:
#line 464 "parser/faustparser.y"
    {(yyval.exp) = boxHBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); ;}
    break;

  case 143:
#line 468 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[-4].exp), cons((yyvsp[-3].exp), (yyvsp[-1].exp))); ;}
    break;

  case 144:
#line 469 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[-3].exp), cons((yyvsp[-2].exp), nil)); ;}
    break;

  case 145:
#line 472 "parser/faustparser.y"
    {(yyval.exp) = tree(yytext);;}
    break;

  case 146:
#line 475 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[0].exp),nil); ;}
    break;

  case 147:
#line 476 "parser/faustparser.y"
    {(yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); ;}
    break;

  case 148:
#line 479 "parser/faustparser.y"
    {(yyval.exp) = tree(0); ;}
    break;

  case 149:
#line 480 "parser/faustparser.y"
    {(yyval.exp) = tree(1); ;}
    break;


    }

/* Line 1037 of yacc.c.  */
#line 2295 "parser/faustparser.cpp"

  yyvsp -= yylen;
  yyssp -= yylen;


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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {

		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 yydestruct ("Error: popping",
                             yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  yydestruct ("Error: discarding", yytoken, &yylval);
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

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

yyvsp -= yylen;
  yyssp -= yylen;
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


      yydestruct ("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token. */
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
  yydestruct ("Error: discarding lookahead",
              yytoken, &yylval);
  yychar = YYEMPTY;
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 483 "parser/faustparser.y"
         


