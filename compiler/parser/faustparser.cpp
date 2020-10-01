/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
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

Tree unquote(char* str)
{
    size_t size = strlen(str) + 1;
    
    //-----------copy unquoted filename-------------
    char* buf = (char*)alloca(size);
    size_t j=0;

    if (str[0] == '"') {
        //it is a quoted string, we remove the quotes
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


#line 137 "faustparser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_FAUSTPARSER_HPP_INCLUDED
# define YY_YY_FAUSTPARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    WITH = 258,
    LETREC = 259,
    SPLIT = 260,
    MIX = 261,
    SEQ = 262,
    PAR = 263,
    REC = 264,
    LT = 265,
    LE = 266,
    EQ = 267,
    GT = 268,
    GE = 269,
    NE = 270,
    ADD = 271,
    SUB = 272,
    OR = 273,
    MUL = 274,
    DIV = 275,
    MOD = 276,
    AND = 277,
    XOR = 278,
    LSH = 279,
    RSH = 280,
    POWOP = 281,
    FDELAY = 282,
    DELAY1 = 283,
    APPL = 284,
    DOT = 285,
    MEM = 286,
    PREFIX = 287,
    INTCAST = 288,
    FLOATCAST = 289,
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
    DEF = 342,
    IMPORT = 343,
    COMPONENT = 344,
    LIBRARY = 345,
    ENVIRONMENT = 346,
    WAVEFORM = 347,
    ROUTE = 348,
    ENABLE = 349,
    CONTROL = 350,
    IPAR = 351,
    ISEQ = 352,
    ISUM = 353,
    IPROD = 354,
    INPUTS = 355,
    OUTPUTS = 356,
    ONDEMAND = 357,
    STRING = 358,
    FSTRING = 359,
    IDENT = 360,
    EXTRA = 361,
    DECLARE = 362,
    CASE = 363,
    ARROW = 364,
    BDOC = 365,
    EDOC = 366,
    BEQN = 367,
    EEQN = 368,
    BDGM = 369,
    EDGM = 370,
    BLST = 371,
    ELST = 372,
    BMETADATA = 373,
    EMETADATA = 374,
    DOCCHAR = 375,
    NOTICE = 376,
    LISTING = 377,
    LSTTRUE = 378,
    LSTFALSE = 379,
    LSTDEPENDENCIES = 380,
    LSTMDOCTAGS = 381,
    LSTDISTRIBUTED = 382,
    LSTEQ = 383,
    LSTQ = 384
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 73 "faustparser.y"

	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;

#line 326 "faustparser.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_FAUSTPARSER_HPP_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   746

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  130
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  219
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  481

#define YYUNDEFTOK  2
#define YYMAXUTOK   384


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
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
     125,   126,   127,   128,   129
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   319,   319,   322,   323,   325,   326,   330,   331,   338,
     339,   342,   343,   344,   345,   346,   347,   351,   352,   353,
     354,   355,   358,   359,   362,   363,   364,   365,   366,   367,
     370,   371,   374,   377,   380,   383,   386,   387,   390,   391,
     392,   395,   396,   399,   402,   403,   404,   407,   408,   411,
     414,   417,   418,   421,   422,   423,   424,   425,   426,   427,
     428,   431,   432,   433,   434,   435,   436,   437,   438,   439,
     441,   442,   443,   445,   446,   448,   449,   450,   451,   452,
     453,   455,   456,   458,   461,   462,   464,   465,   467,   468,
     470,   471,   473,   474,   476,   477,   479,   480,   481,   482,
     483,   484,   486,   487,   488,   490,   491,   493,   494,   495,
     496,   497,   498,   500,   501,   502,   505,   506,   507,   508,
     509,   510,   511,   513,   514,   515,   516,   517,   518,   520,
     521,   522,   524,   525,   527,   528,   529,   532,   533,   535,
     536,   538,   539,   541,   542,   545,   547,   548,   549,   550,
     551,   552,   553,   554,   555,   556,   557,   558,   559,   560,
     561,   562,   563,   564,   565,   567,   568,   569,   570,   572,
     573,   574,   579,   582,   587,   588,   591,   592,   593,   594,
     595,   598,   601,   604,   605,   610,   614,   618,   622,   627,
     630,   633,   638,   642,   645,   650,   653,   656,   659,   662,
     665,   668,   671,   675,   678,   681,   688,   689,   690,   692,
     693,   694,   697,   700,   701,   704,   705,   708,   712,   713
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WITH", "LETREC", "SPLIT", "MIX", "SEQ",
  "PAR", "REC", "LT", "LE", "EQ", "GT", "GE", "NE", "ADD", "SUB", "OR",
  "MUL", "DIV", "MOD", "AND", "XOR", "LSH", "RSH", "POWOP", "FDELAY",
  "DELAY1", "APPL", "DOT", "MEM", "PREFIX", "INTCAST", "FLOATCAST",
  "FFUNCTION", "FCONSTANT", "FVARIABLE", "BUTTON", "CHECKBOX", "VSLIDER",
  "HSLIDER", "NENTRY", "VGROUP", "HGROUP", "TGROUP", "HBARGRAPH",
  "VBARGRAPH", "SOUNDFILE", "ATTACH", "ACOS", "ASIN", "ATAN", "ATAN2",
  "COS", "SIN", "TAN", "EXP", "LOG", "LOG10", "POWFUN", "SQRT", "ABS",
  "MIN", "MAX", "FMOD", "REMAINDER", "FLOOR", "CEIL", "RINT", "RDTBL",
  "RWTBL", "SELECT2", "SELECT3", "INT", "FLOAT", "LAMBDA", "WIRE", "CUT",
  "ENDDEF", "VIRG", "LPAR", "RPAR", "LBRAQ", "RBRAQ", "LCROC", "RCROC",
  "DEF", "IMPORT", "COMPONENT", "LIBRARY", "ENVIRONMENT", "WAVEFORM",
  "ROUTE", "ENABLE", "CONTROL", "IPAR", "ISEQ", "ISUM", "IPROD", "INPUTS",
  "OUTPUTS", "ONDEMAND", "STRING", "FSTRING", "IDENT", "EXTRA", "DECLARE",
  "CASE", "ARROW", "BDOC", "EDOC", "BEQN", "EEQN", "BDGM", "EDGM", "BLST",
  "ELST", "BMETADATA", "EMETADATA", "DOCCHAR", "NOTICE", "LISTING",
  "LSTTRUE", "LSTFALSE", "LSTDEPENDENCIES", "LSTMDOCTAGS",
  "LSTDISTRIBUTED", "LSTEQ", "LSTQ", "$accept", "program", "stmtlist",
  "deflist", "reclist", "vallist", "number", "statement", "doc", "docelem",
  "doctxt", "doceqn", "docdgm", "docntc", "doclst", "lstattrlist",
  "lstattrdef", "lstattrval", "docmtd", "definition", "recinition",
  "defname", "recname", "params", "expression", "infixexp", "primitive",
  "ident", "name", "arglist", "argument", "string", "uqstring", "fstring",
  "fpar", "fseq", "fsum", "fprod", "finputs", "foutputs", "fondemand",
  "ffunction", "fconst", "fvariable", "button", "checkbox", "vslider",
  "hslider", "nentry", "vgroup", "hgroup", "tgroup", "vbargraph",
  "hbargraph", "soundfile", "signature", "fun", "typelist", "rulelist",
  "rule", "type", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
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
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384
};
# endif

#define YYPACT_NINF (-371)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -371,    68,    32,  -371,    18,    20,  -371,   -21,  -371,  -371,
    -371,    38,  -371,  -371,    11,  -371,   -17,   266,   416,   416,
    -371,    59,  -371,    43,    75,  -371,   416,   416,  -371,   -21,
    -371,  -371,    28,  -371,  -371,  -371,  -371,  -371,  -371,  -371,
    -371,  -371,  -371,  -371,   -35,   176,  -371,  -371,  -371,  -371,
    -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,
     119,   136,   216,   222,   233,   238,   261,   268,   271,   276,
     285,   295,   300,   302,  -371,  -371,  -371,  -371,  -371,  -371,
    -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,
    -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,
    -371,   307,  -371,  -371,   416,   308,   312,   186,   257,   320,
    -371,  -371,   321,   333,   334,   343,   363,   364,   365,   327,
     544,  -371,  -371,     9,   293,  -371,  -371,  -371,  -371,  -371,
    -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,
    -371,  -371,  -371,  -371,  -371,  -371,   522,   544,    86,   280,
    -371,    16,     6,     1,   376,  -371,  -371,  -371,  -371,  -371,
    -371,   188,   188,   188,    11,    11,    11,    11,    11,    11,
      11,    11,    11,    11,    11,   391,    41,    11,    11,  -371,
     299,   416,   391,   391,   391,   391,   416,   416,   416,   420,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,  -371,   391,
     416,  -371,   416,   298,   416,   416,   416,   416,   421,   436,
     416,   416,   416,   416,   416,  -371,  -371,  -371,  -371,  -371,
    -371,   375,   392,   394,  -371,  -371,  -371,  -371,   515,   448,
     -21,   -21,   491,   507,   595,   598,   606,   613,   615,   616,
     618,   619,   620,    23,  -371,  -371,   569,   570,     5,   160,
     163,  -371,  -371,    19,  -371,   356,   634,   646,   647,   648,
      48,    58,    67,   416,    25,  -371,   560,   560,   560,   560,
     560,   560,   572,   572,   572,   328,   328,   328,   328,   328,
     328,   328,   577,   258,  -371,    29,    27,   293,   416,   293,
     293,   115,  -371,  -371,  -371,   399,   399,   235,   240,  -371,
     530,   531,   532,   214,  -371,    17,   720,   721,  -371,  -371,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   391,
     700,  -371,  -371,  -371,  -371,  -371,  -371,  -371,   299,  -371,
     416,   416,   416,   416,   416,  -371,  -371,  -371,    34,  -371,
    -371,  -371,  -371,  -371,   529,    33,    15,   221,   221,   221,
    -371,  -371,   723,   448,    26,   214,   214,   604,   611,   641,
      74,   154,   189,   658,   663,   138,  -371,   651,  -371,   668,
     673,   678,   683,   688,   624,  -371,  -371,   655,   391,  -371,
    -371,   649,  -371,  -371,   608,   609,   610,    43,    69,  -371,
      82,  -371,   653,   659,   416,   416,   416,  -371,  -371,  -371,
     416,   416,  -371,   416,   416,   416,   416,   416,   416,   416,
    -371,  -371,   416,  -371,  -371,  -371,   660,   448,   185,   188,
    -371,  -371,  -371,   693,   698,   703,   146,   259,   207,   249,
     269,   287,   304,   329,   536,   543,  -371,   662,  -371,    84,
    -371,   416,   416,   416,  -371,  -371,  -371,  -371,  -371,  -371,
    -371,  -371,  -371,  -371,   198,  -371,   708,   713,   718,  -371,
      88,   416,   416,   416,  -371,   278,   341,   493,  -371,  -371,
    -371
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,   172,     0,    22,     4,
      20,     0,    49,    46,     0,   173,     0,    30,     0,     0,
     182,     0,   181,     0,     0,    21,     0,     0,    36,     0,
      34,    23,    24,    25,    26,    27,    28,    29,   107,   108,
     111,   109,   110,   112,    96,    97,   103,    98,    99,   100,
     102,   104,   105,   106,   126,   101,    92,    93,    94,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   113,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,    84,
      85,     0,    90,    91,     0,     0,     0,     0,     0,     0,
     114,   115,     0,     0,     0,     0,     0,     0,     0,     0,
     180,    83,   141,     0,   174,   165,   166,   167,   168,   169,
     170,   171,   146,   147,   148,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,     0,    60,     0,     0,
      18,     0,     0,     0,     0,    31,    86,    87,    88,    89,
     142,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     3,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    68,     0,
       0,     5,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    45,    17,    19,    32,    33,
      35,     0,     0,     0,    37,    43,   218,   219,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    51,   143,     0,     0,     0,     0,
       0,    11,    12,     0,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   215,    75,    76,    79,    77,
      78,    80,    61,    62,    71,    63,    64,    65,    70,    72,
      73,    74,    66,    67,    69,     0,     0,   175,     0,   177,
     178,   176,   179,     5,     7,    57,    58,    56,    55,    59,
       0,     0,     0,     0,   212,     0,     0,     0,   195,   196,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   149,   150,   151,    13,    14,    15,    16,     0,   152,
       0,     0,     0,     0,     0,   189,   190,   191,     0,   145,
     216,    81,    82,     6,     0,     0,     0,     0,     0,     0,
     183,   184,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,     0,    10,     0,
       0,     0,     0,     0,     0,    44,    53,     0,     0,    54,
       8,     0,    41,    42,     0,     0,     0,     0,     0,   209,
       0,   213,     0,     0,     0,     0,     0,   200,   201,   202,
       0,     0,   205,     0,     0,     0,     0,     0,     0,     0,
      48,    50,     0,    38,    39,    40,     0,     0,     0,     0,
     206,   193,   194,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   192,     0,   210,     0,
     214,     0,     0,     0,   204,   203,   144,   153,   185,   186,
     187,   188,   217,    47,     0,   207,     0,     0,     0,   211,
       0,     0,     0,     0,   208,     0,     0,     0,   197,   198,
     199
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -371,  -371,   561,   441,  -371,  -371,   407,  -371,  -371,  -371,
    -371,  -371,  -371,  -371,  -371,  -371,  -371,   -37,  -371,  -260,
    -371,  -371,  -371,  -371,     3,   -19,  -371,    24,   -11,  -169,
     -81,   -22,   466,     2,  -371,  -371,  -371,  -371,  -371,  -371,
    -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,
    -371,  -371,  -371,  -371,  -371,  -371,  -325,  -370,  -371,   472,
    -159
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   296,   356,   263,   264,     9,    17,    31,
      32,    33,    34,    35,    36,   153,   234,   394,    37,    10,
     390,    11,   391,   253,   146,   120,   121,   122,    16,   123,
     124,    24,    21,   362,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   238,   315,   400,   274,   275,
     401
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     147,   149,   239,   240,   241,    23,     4,   147,   147,   218,
     219,   220,   221,   222,   223,   224,   387,   212,   154,   218,
     219,   220,   221,   222,   223,   224,    12,   338,     4,   151,
     152,   329,    -2,     4,     4,   363,   353,   212,   398,   156,
     157,   295,   212,   388,   218,   219,   220,   221,   222,   223,
     224,   218,   219,   220,   221,   222,   223,   224,   449,   236,
     237,   218,   219,   220,   221,   222,   223,   224,     3,   160,
     218,   219,   220,   221,   222,   223,   224,   218,   219,   220,
     221,   222,   223,   224,    15,   147,    22,   427,    15,   333,
     429,   213,   429,     5,   470,   353,   429,    13,   364,   389,
     265,    14,   447,   339,   348,   330,   273,   176,   399,   349,
       6,   351,     7,   352,    20,     8,   384,   386,   230,    18,
       5,   229,   216,   255,   217,    19,   231,   232,   233,   228,
     345,   297,     6,   299,   300,   301,   302,     6,     6,     7,
     346,   148,     8,   214,   215,   216,    22,   217,   155,   347,
     428,   214,   215,   216,   150,   217,   407,   218,   219,   220,
     221,   222,   223,   224,   430,   226,   465,   147,   147,   147,
     474,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   270,
     271,   272,   218,   219,   220,   221,   222,   223,   224,   254,
     161,   147,   147,   147,   147,   147,   266,   267,   268,   269,
     218,   219,   220,   221,   222,   223,   224,   162,   236,   237,
     412,   236,   237,   305,   306,   307,   308,   309,   454,   316,
     317,   236,   237,   294,   334,   335,   408,   336,   337,   367,
     368,   369,   222,   223,   224,   373,   374,   375,   223,   224,
     158,   159,   218,   219,   220,   221,   222,   223,   224,   379,
     380,   381,   382,   383,   214,   215,   216,   448,   217,   179,
     450,   409,   218,   219,   220,   221,   222,   223,   224,   147,
     469,     6,    12,   214,   215,   216,   208,   217,   209,   456,
     218,   219,   220,   221,   222,   223,   224,   163,   214,   215,
     216,   354,   217,   164,   147,   147,   147,   218,   219,   220,
     221,   222,   223,   224,   165,   259,   260,   360,   361,   166,
      12,   395,   396,   433,   434,   435,   370,   371,   372,   436,
     437,   457,   218,   219,   220,   221,   222,   223,   224,   210,
     180,   455,   167,   211,   392,   393,   214,   215,   216,   168,
     217,   458,   169,   376,   206,   207,   208,   170,   209,   227,
     478,   214,   215,   216,   340,   217,   171,   402,   403,   459,
     466,   467,   468,   261,   262,   426,   172,    25,    26,    12,
      27,   173,    28,   174,    29,   298,   460,    30,   175,   177,
     475,   476,   477,   178,   147,   147,   147,   147,   147,   147,
     147,   181,   182,   147,   220,   221,   222,   223,   224,   210,
     189,   461,   421,   211,   183,   184,   438,   439,   440,   441,
     442,   443,   444,   479,   185,   445,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,   186,   187,   188,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   235,     6,   104,   214,   215,
     216,   273,   217,   310,   303,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   304,
     311,     6,   312,   313,   119,   218,   219,   220,   221,   222,
     223,   224,   218,   219,   220,   221,   222,   223,   224,   218,
     219,   220,   221,   222,   223,   224,   218,   219,   220,   221,
     222,   223,   224,   314,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   318,   209,   480,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   319,
     209,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   225,   209,   320,   207,   208,   321,   209,   385,   214,
     215,   216,   404,   217,   322,   462,   214,   215,   216,   405,
     217,   323,   463,   324,   325,   210,   326,   327,   328,   211,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   210,   341,   256,   257,   211,   214,   215,   216,   406,
     217,   331,   332,   210,   342,   343,   344,   211,   210,   357,
     358,   359,   211,   214,   215,   216,   410,   217,   214,   215,
     216,   411,   217,   214,   215,   216,   414,   217,   214,   215,
     216,   415,   217,   214,   215,   216,   416,   217,   214,   215,
     216,   417,   217,   214,   215,   216,   418,   217,   214,   215,
     216,   451,   217,   214,   215,   216,   452,   217,   214,   215,
     216,   453,   217,   214,   215,   216,   471,   217,   214,   215,
     216,   472,   217,   214,   215,   216,   473,   217,   365,   366,
     377,   397,   413,   419,   420,   431,   422,   423,   424,   425,
     258,   432,   446,   464,   355,   378,   350
};

static const yytype_int16 yycheck[] =
{
      19,    23,   161,   162,   163,    16,     1,    26,    27,     3,
       4,     5,     6,     7,     8,     9,     1,     8,    29,     3,
       4,     5,     6,     7,     8,     9,     2,     8,     1,    26,
      27,     8,     0,     1,     1,    18,   296,     8,   363,    74,
      75,   210,     8,    28,     3,     4,     5,     6,     7,     8,
       9,     3,     4,     5,     6,     7,     8,     9,   428,    33,
      34,     3,     4,     5,     6,     7,     8,     9,     0,    45,
       3,     4,     5,     6,     7,     8,     9,     3,     4,     5,
       6,     7,     8,     9,   105,   104,   103,    18,   105,    84,
       8,    82,     8,    88,   464,   355,     8,    79,    81,    84,
     181,    81,   427,    84,   273,    82,    81,   104,    82,    84,
     105,    82,   107,    86,   103,   110,    82,    84,   117,    81,
      88,   115,     7,    82,     9,    87,   125,   126,   127,   113,
      82,   212,   105,   214,   215,   216,   217,   105,   105,   107,
      82,    82,   110,     5,     6,     7,   103,     9,   120,    82,
      81,     5,     6,     7,    79,     9,    82,     3,     4,     5,
       6,     7,     8,     9,    82,    79,    82,   186,   187,   188,
      82,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   186,
     187,   188,     3,     4,     5,     6,     7,     8,     9,   175,
      81,   220,   221,   222,   223,   224,   182,   183,   184,   185,
       3,     4,     5,     6,     7,     8,     9,    81,    33,    34,
      82,    33,    34,   220,   221,   222,   223,   224,    82,   240,
     241,    33,    34,   209,    74,    75,    82,    74,    75,   320,
     321,   322,     7,     8,     9,   326,   327,   328,     8,     9,
      74,    75,     3,     4,     5,     6,     7,     8,     9,   340,
     341,   342,   343,   344,     5,     6,     7,    82,     9,    83,
     429,    82,     3,     4,     5,     6,     7,     8,     9,   298,
      82,   105,   258,     5,     6,     7,    28,     9,    30,    82,
       3,     4,     5,     6,     7,     8,     9,    81,     5,     6,
       7,   298,     9,    81,   323,   324,   325,     3,     4,     5,
       6,     7,     8,     9,    81,    16,    17,   103,   104,    81,
     296,   358,   359,   404,   405,   406,   323,   324,   325,   410,
     411,    82,     3,     4,     5,     6,     7,     8,     9,    81,
      83,    82,    81,    85,   123,   124,     5,     6,     7,    81,
       9,    82,    81,   329,    26,    27,    28,    81,    30,    79,
      82,     5,     6,     7,     8,     9,    81,   365,   366,    82,
     451,   452,   453,    74,    75,   397,    81,   111,   112,   355,
     114,    81,   116,    81,   118,    87,    82,   121,    81,    81,
     471,   472,   473,    81,   413,   414,   415,   416,   417,   418,
     419,    81,    81,   422,     5,     6,     7,     8,     9,    81,
      83,    82,   388,    85,    81,    81,   413,   414,   415,   416,
     417,   418,   419,    82,    81,   422,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    81,    81,    81,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,   119,   105,    81,     5,     6,
       7,    81,     9,   128,    83,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,    83,
     128,   105,   128,     8,   108,     3,     4,     5,     6,     7,
       8,     9,     3,     4,     5,     6,     7,     8,     9,     3,
       4,     5,     6,     7,     8,     9,     3,     4,     5,     6,
       7,     8,     9,   105,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    82,    30,    82,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    82,
      30,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    79,    30,     8,    27,    28,     8,    30,    79,     5,
       6,     7,     8,     9,     8,    79,     5,     6,     7,     8,
       9,     8,    79,     8,     8,    81,     8,     8,     8,    85,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,    81,     8,   177,   178,    85,     5,     6,     7,     8,
       9,    82,    82,    81,     8,     8,     8,    85,    81,   129,
     129,   129,    85,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     5,     6,
       7,     8,     9,     5,     6,     7,     8,     9,     8,     8,
      30,     8,    81,   109,    79,    82,    87,   129,   129,   129,
     179,    82,    82,    81,   303,   338,   274
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   131,   132,     0,     1,    88,   105,   107,   110,   137,
     149,   151,   157,    79,    81,   105,   158,   138,    81,    87,
     103,   162,   103,   158,   161,   111,   112,   114,   116,   118,
     121,   139,   140,   141,   142,   143,   144,   148,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    81,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   108,
     155,   156,   157,   159,   160,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   154,   155,    82,   161,
      79,   154,   154,   145,   158,   120,    74,    75,    74,    75,
     157,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,   154,    81,    81,    83,
      83,    81,    81,    81,    81,    81,    81,    81,    81,    83,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    30,
      81,    85,     8,    82,     5,     6,     7,     9,     3,     4,
       5,     6,     7,     8,     9,    79,    79,    79,   113,   115,
     117,   125,   126,   127,   146,   119,    33,    34,   185,   190,
     190,   190,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   153,   157,    82,   162,   162,   132,    16,
      17,    74,    75,   135,   136,   160,   157,   157,   157,   157,
     154,   154,   154,    81,   188,   189,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   157,   159,   133,   160,    87,   160,
     160,   160,   160,    83,    83,   154,   154,   154,   154,   154,
     128,   128,   128,     8,   105,   186,   158,   158,    82,    82,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
      82,    82,    82,    84,    74,    75,    74,    75,     8,    84,
       8,     8,     8,     8,     8,    82,    82,    82,   159,    84,
     189,    82,    86,   149,   154,   133,   134,   129,   129,   129,
     103,   104,   163,    18,    81,     8,     8,   160,   160,   160,
     154,   154,   154,   160,   160,   160,   157,    30,   136,   160,
     160,   160,   160,   160,    82,    79,    84,     1,    28,    84,
     150,   152,   123,   124,   147,   147,   147,     8,   186,    82,
     187,   190,   163,   163,     8,     8,     8,    82,    82,    82,
       8,     8,    82,    81,     8,     8,     8,     8,     8,   109,
      79,   157,    87,   129,   129,   129,   161,    18,    81,     8,
      82,    82,    82,   160,   160,   160,   160,   160,   154,   154,
     154,   154,   154,   154,   154,   154,    82,   186,    82,   187,
     190,     8,     8,     8,    82,    82,    82,    82,    82,    82,
      82,    82,    79,    79,    81,    82,   160,   160,   160,    82,
     187,     8,     8,     8,    82,   160,   160,   160,    82,    82,
      82
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   130,   131,   132,   132,   133,   133,   134,   134,   135,
     135,   136,   136,   136,   136,   136,   136,   137,   137,   137,
     137,   137,   138,   138,   139,   139,   139,   139,   139,   139,
     140,   140,   141,   142,   143,   144,   145,   145,   146,   146,
     146,   147,   147,   148,   149,   149,   149,   150,   150,   151,
     152,   153,   153,   154,   154,   154,   154,   154,   154,   154,
     154,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   157,   158,   159,   159,   160,   160,   160,   160,
     160,   161,   162,   163,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   185,   185,   185,
     185,   185,   186,   187,   187,   188,   188,   189,   190,   190
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     0,     2,     0,     2,     1,
       3,     1,     1,     2,     2,     2,     2,     5,     4,     5,
       1,     3,     0,     2,     1,     1,     1,     1,     1,     1,
       0,     2,     3,     3,     1,     3,     0,     2,     5,     5,
       5,     1,     1,     3,     7,     4,     2,     4,     2,     1,
       2,     1,     3,     5,     5,     3,     3,     3,     3,     3,
       1,     3,     3,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     4,     4,     1,     1,     1,     2,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     8,     4,     1,     1,     1,     4,
       4,     4,     4,     8,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     8,     8,     8,     8,     4,
       4,     4,     8,     7,     7,     4,     4,    12,    12,    12,
       6,     6,     6,     8,     8,     6,     5,     7,     9,     4,
       6,     8,     1,     1,     3,     1,     2,     6,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
      yychar = yylex ();
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

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
#line 319 "faustparser.y"
                                                                        { (yyval.exp) = (yyvsp[0].exp); gGlobal->gResult = formatDefinitions((yyval.exp)); }
#line 1906 "faustparser.cpp"
    break;

  case 3:
#line 322 "faustparser.y"
                                                { (yyval.exp) = gGlobal->nil; }
#line 1912 "faustparser.cpp"
    break;

  case 4:
#line 323 "faustparser.y"
                                                                { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1918 "faustparser.cpp"
    break;

  case 5:
#line 325 "faustparser.y"
                                                { (yyval.exp) = gGlobal->nil; }
#line 1924 "faustparser.cpp"
    break;

  case 6:
#line 326 "faustparser.y"
                                                                { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1930 "faustparser.cpp"
    break;

  case 7:
#line 330 "faustparser.y"
                                                        { (yyval.exp) = gGlobal->nil; }
#line 1936 "faustparser.cpp"
    break;

  case 8:
#line 331 "faustparser.y"
                                                        { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 1942 "faustparser.cpp"
    break;

  case 9:
#line 338 "faustparser.y"
                                                      { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1948 "faustparser.cpp"
    break;

  case 10:
#line 339 "faustparser.y"
                                                      { gGlobal->gWaveForm.push_back((yyvsp[0].exp)); }
#line 1954 "faustparser.cpp"
    break;

  case 11:
#line 342 "faustparser.y"
                                                                                { (yyval.exp) = boxInt(atoi(yytext)); }
#line 1960 "faustparser.cpp"
    break;

  case 12:
#line 343 "faustparser.y"
                                                                                        { (yyval.exp) = boxReal(atof(yytext)); }
#line 1966 "faustparser.cpp"
    break;

  case 13:
#line 344 "faustparser.y"
                                                                                { (yyval.exp) = boxInt (atoi(yytext)); }
#line 1972 "faustparser.cpp"
    break;

  case 14:
#line 345 "faustparser.y"
                                                                                { (yyval.exp) = boxReal(atof(yytext)); }
#line 1978 "faustparser.cpp"
    break;

  case 15:
#line 346 "faustparser.y"
                                                                                { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 1984 "faustparser.cpp"
    break;

  case 16:
#line 347 "faustparser.y"
                                                                                { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 1990 "faustparser.cpp"
    break;

  case 17:
#line 351 "faustparser.y"
                                                                { (yyval.exp) = importFile((yyvsp[-2].exp)); }
#line 1996 "faustparser.cpp"
    break;

  case 18:
#line 352 "faustparser.y"
                                                                                { declareMetadata((yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 2002 "faustparser.cpp"
    break;

  case 19:
#line 353 "faustparser.y"
                                                                                { declareDefinitionMetadata((yyvsp[-3].exp),(yyvsp[-2].exp),(yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; }
#line 2008 "faustparser.cpp"
    break;

  case 20:
#line 354 "faustparser.y"
                                                                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2014 "faustparser.cpp"
    break;

  case 21:
#line 355 "faustparser.y"
                                                                                                { declareDoc((yyvsp[-1].exp)); (yyval.exp) = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
#line 2020 "faustparser.cpp"
    break;

  case 22:
#line 358 "faustparser.y"
                                                                                { (yyval.exp) = gGlobal->nil; }
#line 2026 "faustparser.cpp"
    break;

  case 23:
#line 359 "faustparser.y"
                                                                                                { (yyval.exp) = cons ((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 2032 "faustparser.cpp"
    break;

  case 24:
#line 362 "faustparser.y"
                                                                                        { (yyval.exp) = docTxt((yyvsp[0].cppstr)->c_str()); delete (yyvsp[0].cppstr); }
#line 2038 "faustparser.cpp"
    break;

  case 25:
#line 363 "faustparser.y"
                                                                                                        { (yyval.exp) = docEqn((yyvsp[0].exp)); }
#line 2044 "faustparser.cpp"
    break;

  case 26:
#line 364 "faustparser.y"
                                                                                                        { (yyval.exp) = docDgm((yyvsp[0].exp)); }
#line 2050 "faustparser.cpp"
    break;

  case 27:
#line 365 "faustparser.y"
                                                                                                        { (yyval.exp) = docNtc(); }
#line 2056 "faustparser.cpp"
    break;

  case 28:
#line 366 "faustparser.y"
                                                                                        { (yyval.exp) = docLst(); }
#line 2062 "faustparser.cpp"
    break;

  case 29:
#line 367 "faustparser.y"
                                                                                                        { (yyval.exp) = docMtd((yyvsp[0].exp)); }
#line 2068 "faustparser.cpp"
    break;

  case 30:
#line 370 "faustparser.y"
                                                                                { (yyval.cppstr) = new string(); }
#line 2074 "faustparser.cpp"
    break;

  case 31:
#line 371 "faustparser.y"
                                                                                                { (yyval.cppstr) = &((yyvsp[-1].cppstr)->append(yytext)); }
#line 2080 "faustparser.cpp"
    break;

  case 32:
#line 374 "faustparser.y"
                                                                        { (yyval.exp) = (yyvsp[-1].exp); }
#line 2086 "faustparser.cpp"
    break;

  case 33:
#line 377 "faustparser.y"
                                                                        { (yyval.exp) = (yyvsp[-1].exp); }
#line 2092 "faustparser.cpp"
    break;

  case 34:
#line 380 "faustparser.y"
                                                                                        { }
#line 2098 "faustparser.cpp"
    break;

  case 35:
#line 383 "faustparser.y"
                                                                        { }
#line 2104 "faustparser.cpp"
    break;

  case 36:
#line 386 "faustparser.y"
                                                                                        { }
#line 2110 "faustparser.cpp"
    break;

  case 37:
#line 387 "faustparser.y"
                                                                                        { }
#line 2116 "faustparser.cpp"
    break;

  case 38:
#line 390 "faustparser.y"
                                                                        { gGlobal->gLstDependenciesSwitch = (yyvsp[-1].b); }
#line 2122 "faustparser.cpp"
    break;

  case 39:
#line 391 "faustparser.y"
                                                                                        { gGlobal->gStripDocSwitch = (yyvsp[-1].b); gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; }
#line 2128 "faustparser.cpp"
    break;

  case 40:
#line 392 "faustparser.y"
                                                                                        { gGlobal->gLstDistributedSwitch = (yyvsp[-1].b); }
#line 2134 "faustparser.cpp"
    break;

  case 41:
#line 395 "faustparser.y"
                                                                                                { (yyval.b) = true; }
#line 2140 "faustparser.cpp"
    break;

  case 42:
#line 396 "faustparser.y"
                                                                                                        { (yyval.b) = false; }
#line 2146 "faustparser.cpp"
    break;

  case 43:
#line 399 "faustparser.y"
                                                                        { (yyval.exp) = (yyvsp[-1].exp); }
#line 2152 "faustparser.cpp"
    break;

  case 44:
#line 402 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),(yyvsp[-1].exp))); setDefProp((yyvsp[-6].exp), yyfilename, yylineno); }
#line 2158 "faustparser.cpp"
    break;

  case 45:
#line 403 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp)));  setDefProp((yyvsp[-3].exp), yyfilename, yylineno); }
#line 2164 "faustparser.cpp"
    break;

  case 46:
#line 404 "faustparser.y"
                                                                                                { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 2170 "faustparser.cpp"
    break;

  case 47:
#line 407 "faustparser.y"
                                                                        { (yyval.exp) = cons((yyvsp[-3].exp),cons(gGlobal->nil,(yyvsp[-1].exp))); setDefProp((yyvsp[-3].exp), yyfilename, yylineno); }
#line 2176 "faustparser.cpp"
    break;

  case 48:
#line 408 "faustparser.y"
                                                                                { (yyval.exp) = gGlobal->nil; yyerr++; }
#line 2182 "faustparser.cpp"
    break;

  case 49:
#line 411 "faustparser.y"
                                                                                                { (yyval.exp)=(yyvsp[0].exp); }
#line 2188 "faustparser.cpp"
    break;

  case 50:
#line 414 "faustparser.y"
                                                                                        { (yyval.exp)=(yyvsp[0].exp); }
#line 2194 "faustparser.cpp"
    break;

  case 51:
#line 417 "faustparser.y"
                                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2200 "faustparser.cpp"
    break;

  case 52:
#line 418 "faustparser.y"
                                                                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2206 "faustparser.cpp"
    break;

  case 53:
#line 421 "faustparser.y"
                                                                { (yyval.exp) = boxWithLocalDef((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2212 "faustparser.cpp"
    break;

  case 54:
#line 422 "faustparser.y"
                                                        { (yyval.exp) = boxWithRecDef  ((yyvsp[-4].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2218 "faustparser.cpp"
    break;

  case 55:
#line 423 "faustparser.y"
                                                                { (yyval.exp) = boxPar((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2224 "faustparser.cpp"
    break;

  case 56:
#line 424 "faustparser.y"
                                                                                { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2230 "faustparser.cpp"
    break;

  case 57:
#line 425 "faustparser.y"
                                                                            { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2236 "faustparser.cpp"
    break;

  case 58:
#line 426 "faustparser.y"
                                                                                { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2242 "faustparser.cpp"
    break;

  case 59:
#line 427 "faustparser.y"
                                                                                { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2248 "faustparser.cpp"
    break;

  case 60:
#line 428 "faustparser.y"
                                                                                            { (yyval.exp) = (yyvsp[0].exp); }
#line 2254 "faustparser.cpp"
    break;

  case 61:
#line 431 "faustparser.y"
                                                        { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAdd)); }
#line 2260 "faustparser.cpp"
    break;

  case 62:
#line 432 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2266 "faustparser.cpp"
    break;

  case 63:
#line 433 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigMul)); }
#line 2272 "faustparser.cpp"
    break;

  case 64:
#line 434 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigDiv)); }
#line 2278 "faustparser.cpp"
    break;

  case 65:
#line 435 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRem)); }
#line 2284 "faustparser.cpp"
    break;

  case 66:
#line 436 "faustparser.y"
                                            { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),gGlobal->gPowPrim->box()); }
#line 2290 "faustparser.cpp"
    break;

  case 67:
#line 437 "faustparser.y"
                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigFixDelay)); }
#line 2296 "faustparser.cpp"
    break;

  case 68:
#line 438 "faustparser.y"
                                                                        { (yyval.exp) = boxSeq((yyvsp[-1].exp),boxPrim1(sigDelay1)); }
#line 2302 "faustparser.cpp"
    break;

  case 69:
#line 439 "faustparser.y"
                                                                { (yyval.exp) = boxAccess((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2308 "faustparser.cpp"
    break;

  case 70:
#line 441 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigAND)); }
#line 2314 "faustparser.cpp"
    break;

  case 71:
#line 442 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigOR)); }
#line 2320 "faustparser.cpp"
    break;

  case 72:
#line 443 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigXOR)); }
#line 2326 "faustparser.cpp"
    break;

  case 73:
#line 445 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLeftShift)); }
#line 2332 "faustparser.cpp"
    break;

  case 74:
#line 446 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigRightShift)); }
#line 2338 "faustparser.cpp"
    break;

  case 75:
#line 448 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLT)); }
#line 2344 "faustparser.cpp"
    break;

  case 76:
#line 449 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigLE)); }
#line 2350 "faustparser.cpp"
    break;

  case 77:
#line 450 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGT)); }
#line 2356 "faustparser.cpp"
    break;

  case 78:
#line 451 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigGE)); }
#line 2362 "faustparser.cpp"
    break;

  case 79:
#line 452 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigEQ)); }
#line 2368 "faustparser.cpp"
    break;

  case 80:
#line 453 "faustparser.y"
                                                                { (yyval.exp) = boxSeq(boxPar((yyvsp[-2].exp),(yyvsp[0].exp)),boxPrim2(sigNE)); }
#line 2374 "faustparser.cpp"
    break;

  case 81:
#line 455 "faustparser.y"
                                                                                { (yyval.exp) = buildBoxAppl((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 2380 "faustparser.cpp"
    break;

  case 82:
#line 456 "faustparser.y"
                                                                                { (yyval.exp) = boxModifLocalDef((yyvsp[-3].exp),formatDefinitions((yyvsp[-1].exp))); }
#line 2386 "faustparser.cpp"
    break;

  case 83:
#line 458 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2392 "faustparser.cpp"
    break;

  case 84:
#line 461 "faustparser.y"
                                                                                { (yyval.exp) = boxInt(atoi(yytext)); }
#line 2398 "faustparser.cpp"
    break;

  case 85:
#line 462 "faustparser.y"
                                                                                        { (yyval.exp) = boxReal(atof(yytext)); }
#line 2404 "faustparser.cpp"
    break;

  case 86:
#line 464 "faustparser.y"
                                                                                { (yyval.exp) = boxInt (atoi(yytext)); }
#line 2410 "faustparser.cpp"
    break;

  case 87:
#line 465 "faustparser.y"
                                                                                { (yyval.exp) = boxReal(atof(yytext)); }
#line 2416 "faustparser.cpp"
    break;

  case 88:
#line 467 "faustparser.y"
                                                                                { (yyval.exp) = boxInt ( -atoi(yytext) ); }
#line 2422 "faustparser.cpp"
    break;

  case 89:
#line 468 "faustparser.y"
                                                                                { (yyval.exp) = boxReal( -atof(yytext) ); }
#line 2428 "faustparser.cpp"
    break;

  case 90:
#line 470 "faustparser.y"
                                                                                        { (yyval.exp) = boxWire(); }
#line 2434 "faustparser.cpp"
    break;

  case 91:
#line 471 "faustparser.y"
                                                                                        { (yyval.exp) = boxCut(); }
#line 2440 "faustparser.cpp"
    break;

  case 92:
#line 473 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim1(sigDelay1); }
#line 2446 "faustparser.cpp"
    break;

  case 93:
#line 474 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigPrefix); }
#line 2452 "faustparser.cpp"
    break;

  case 94:
#line 476 "faustparser.y"
                                                                { (yyval.exp) = boxPrim1(sigIntCast); }
#line 2458 "faustparser.cpp"
    break;

  case 95:
#line 477 "faustparser.y"
                                                                                { (yyval.exp) = boxPrim1(sigFloatCast); }
#line 2464 "faustparser.cpp"
    break;

  case 96:
#line 479 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigAdd); }
#line 2470 "faustparser.cpp"
    break;

  case 97:
#line 480 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigSub); }
#line 2476 "faustparser.cpp"
    break;

  case 98:
#line 481 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigMul); }
#line 2482 "faustparser.cpp"
    break;

  case 99:
#line 482 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigDiv); }
#line 2488 "faustparser.cpp"
    break;

  case 100:
#line 483 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigRem); }
#line 2494 "faustparser.cpp"
    break;

  case 101:
#line 484 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigFixDelay); }
#line 2500 "faustparser.cpp"
    break;

  case 102:
#line 486 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigAND); }
#line 2506 "faustparser.cpp"
    break;

  case 103:
#line 487 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigOR); }
#line 2512 "faustparser.cpp"
    break;

  case 104:
#line 488 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigXOR); }
#line 2518 "faustparser.cpp"
    break;

  case 105:
#line 490 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigLeftShift); }
#line 2524 "faustparser.cpp"
    break;

  case 106:
#line 491 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigRightShift); }
#line 2530 "faustparser.cpp"
    break;

  case 107:
#line 493 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigLT); }
#line 2536 "faustparser.cpp"
    break;

  case 108:
#line 494 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigLE); }
#line 2542 "faustparser.cpp"
    break;

  case 109:
#line 495 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigGT); }
#line 2548 "faustparser.cpp"
    break;

  case 110:
#line 496 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigGE); }
#line 2554 "faustparser.cpp"
    break;

  case 111:
#line 497 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigEQ); }
#line 2560 "faustparser.cpp"
    break;

  case 112:
#line 498 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigNE); }
#line 2566 "faustparser.cpp"
    break;

  case 113:
#line 500 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim2(sigAttach); }
#line 2572 "faustparser.cpp"
    break;

  case 114:
#line 501 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigEnable); }
#line 2578 "faustparser.cpp"
    break;

  case 115:
#line 502 "faustparser.y"
                                                { (yyval.exp) = boxPrim2(sigControl); }
#line 2584 "faustparser.cpp"
    break;

  case 116:
#line 505 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAcosPrim->box(); }
#line 2590 "faustparser.cpp"
    break;

  case 117:
#line 506 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAsinPrim->box(); }
#line 2596 "faustparser.cpp"
    break;

  case 118:
#line 507 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAtanPrim->box(); }
#line 2602 "faustparser.cpp"
    break;

  case 119:
#line 508 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAtan2Prim->box(); }
#line 2608 "faustparser.cpp"
    break;

  case 120:
#line 509 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gCosPrim->box(); }
#line 2614 "faustparser.cpp"
    break;

  case 121:
#line 510 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gSinPrim->box(); }
#line 2620 "faustparser.cpp"
    break;

  case 122:
#line 511 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gTanPrim->box(); }
#line 2626 "faustparser.cpp"
    break;

  case 123:
#line 513 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gExpPrim->box(); }
#line 2632 "faustparser.cpp"
    break;

  case 124:
#line 514 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gLogPrim->box(); }
#line 2638 "faustparser.cpp"
    break;

  case 125:
#line 515 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gLog10Prim->box(); }
#line 2644 "faustparser.cpp"
    break;

  case 126:
#line 516 "faustparser.y"
                                                { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2650 "faustparser.cpp"
    break;

  case 127:
#line 517 "faustparser.y"
                                                { (yyval.exp) = gGlobal->gPowPrim->box(); }
#line 2656 "faustparser.cpp"
    break;

  case 128:
#line 518 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gSqrtPrim->box(); }
#line 2662 "faustparser.cpp"
    break;

  case 129:
#line 520 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gAbsPrim->box(); }
#line 2668 "faustparser.cpp"
    break;

  case 130:
#line 521 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gMinPrim->box(); }
#line 2674 "faustparser.cpp"
    break;

  case 131:
#line 522 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gMaxPrim->box(); }
#line 2680 "faustparser.cpp"
    break;

  case 132:
#line 524 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gFmodPrim->box(); }
#line 2686 "faustparser.cpp"
    break;

  case 133:
#line 525 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gRemainderPrim->box(); }
#line 2692 "faustparser.cpp"
    break;

  case 134:
#line 527 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gFloorPrim->box(); }
#line 2698 "faustparser.cpp"
    break;

  case 135:
#line 528 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gCeilPrim->box(); }
#line 2704 "faustparser.cpp"
    break;

  case 136:
#line 529 "faustparser.y"
                                                                                        { (yyval.exp) = gGlobal->gRintPrim->box(); }
#line 2710 "faustparser.cpp"
    break;

  case 137:
#line 532 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim3(sigReadOnlyTable); }
#line 2716 "faustparser.cpp"
    break;

  case 138:
#line 533 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim5(sigWriteReadTable); }
#line 2722 "faustparser.cpp"
    break;

  case 139:
#line 535 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim3(sigSelect2); }
#line 2728 "faustparser.cpp"
    break;

  case 140:
#line 536 "faustparser.y"
                                                                                        { (yyval.exp) = boxPrim4(sigSelect3); }
#line 2734 "faustparser.cpp"
    break;

  case 141:
#line 538 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp);  setUseProp((yyvsp[0].exp), yyfilename, yylineno);}
#line 2740 "faustparser.cpp"
    break;

  case 142:
#line 539 "faustparser.y"
                                                { (yyval.exp) = boxSeq(boxPar(boxInt(0),(yyvsp[0].exp)),boxPrim2(sigSub)); }
#line 2746 "faustparser.cpp"
    break;

  case 143:
#line 541 "faustparser.y"
                                                                                { (yyval.exp) = (yyvsp[-1].exp); }
#line 2752 "faustparser.cpp"
    break;

  case 144:
#line 543 "faustparser.y"
                                                                                                { (yyval.exp) = buildBoxAbstr((yyvsp[-5].exp),(yyvsp[-1].exp)); }
#line 2758 "faustparser.cpp"
    break;

  case 145:
#line 545 "faustparser.y"
                                                                        { (yyval.exp) = boxCase(checkRulelist((yyvsp[-1].exp))); }
#line 2764 "faustparser.cpp"
    break;

  case 146:
#line 547 "faustparser.y"
                                                                                        { (yyval.exp) = boxFFun((yyvsp[0].exp)); }
#line 2770 "faustparser.cpp"
    break;

  case 147:
#line 548 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2776 "faustparser.cpp"
    break;

  case 148:
#line 549 "faustparser.y"
                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2782 "faustparser.cpp"
    break;

  case 149:
#line 550 "faustparser.y"
                                                { (yyval.exp) = boxComponent((yyvsp[-1].exp)); }
#line 2788 "faustparser.cpp"
    break;

  case 150:
#line 551 "faustparser.y"
                                                { (yyval.exp) = boxLibrary((yyvsp[-1].exp)); }
#line 2794 "faustparser.cpp"
    break;

  case 151:
#line 552 "faustparser.y"
                                                   { (yyval.exp) = boxWithLocalDef(boxEnvironment(),formatDefinitions((yyvsp[-1].exp))); }
#line 2800 "faustparser.cpp"
    break;

  case 152:
#line 553 "faustparser.y"
                                                { (yyval.exp) = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); }
#line 2806 "faustparser.cpp"
    break;

  case 153:
#line 554 "faustparser.y"
                                                                                                { (yyval.exp) = boxRoute((yyvsp[-5].exp), (yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 2812 "faustparser.cpp"
    break;

  case 154:
#line 555 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2818 "faustparser.cpp"
    break;

  case 155:
#line 556 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2824 "faustparser.cpp"
    break;

  case 156:
#line 557 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2830 "faustparser.cpp"
    break;

  case 157:
#line 558 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2836 "faustparser.cpp"
    break;

  case 158:
#line 559 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2842 "faustparser.cpp"
    break;

  case 159:
#line 560 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2848 "faustparser.cpp"
    break;

  case 160:
#line 561 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2854 "faustparser.cpp"
    break;

  case 161:
#line 562 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2860 "faustparser.cpp"
    break;

  case 162:
#line 563 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2866 "faustparser.cpp"
    break;

  case 163:
#line 564 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2872 "faustparser.cpp"
    break;

  case 164:
#line 565 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2878 "faustparser.cpp"
    break;

  case 165:
#line 567 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2884 "faustparser.cpp"
    break;

  case 166:
#line 568 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2890 "faustparser.cpp"
    break;

  case 167:
#line 569 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2896 "faustparser.cpp"
    break;

  case 168:
#line 570 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2902 "faustparser.cpp"
    break;

  case 169:
#line 572 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2908 "faustparser.cpp"
    break;

  case 170:
#line 573 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2914 "faustparser.cpp"
    break;

  case 171:
#line 574 "faustparser.y"
                                                                                        { (yyval.exp) = (yyvsp[0].exp); }
#line 2920 "faustparser.cpp"
    break;

  case 172:
#line 579 "faustparser.y"
                                                                                { (yyval.exp) = boxIdent(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  }
#line 2926 "faustparser.cpp"
    break;

  case 173:
#line 582 "faustparser.y"
                                                                                { (yyval.exp) = tree(yytext); setUseProp((yyval.exp), yyfilename, yylineno);  }
#line 2932 "faustparser.cpp"
    break;

  case 174:
#line 587 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 2938 "faustparser.cpp"
    break;

  case 175:
#line 588 "faustparser.y"
                                                                        { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 2944 "faustparser.cpp"
    break;

  case 176:
#line 591 "faustparser.y"
                                                                { (yyval.exp) = boxSeq((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2950 "faustparser.cpp"
    break;

  case 177:
#line 592 "faustparser.y"
                                                                        { (yyval.exp) = boxSplit((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2956 "faustparser.cpp"
    break;

  case 178:
#line 593 "faustparser.y"
                                                                        { (yyval.exp) = boxMerge((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2962 "faustparser.cpp"
    break;

  case 179:
#line 594 "faustparser.y"
                                                                        { (yyval.exp) = boxRec((yyvsp[-2].exp),(yyvsp[0].exp)); }
#line 2968 "faustparser.cpp"
    break;

  case 180:
#line 595 "faustparser.y"
                                                                                { (yyval.exp) = (yyvsp[0].exp); }
#line 2974 "faustparser.cpp"
    break;

  case 181:
#line 598 "faustparser.y"
                                                                                { (yyval.exp) = tree(yytext); }
#line 2980 "faustparser.cpp"
    break;

  case 182:
#line 601 "faustparser.y"
                                                                                { (yyval.exp) = unquote(yytext); }
#line 2986 "faustparser.cpp"
    break;

  case 183:
#line 604 "faustparser.y"
                                                                                { (yyval.exp) = tree(yytext); }
#line 2992 "faustparser.cpp"
    break;

  case 184:
#line 605 "faustparser.y"
                                                                                        { (yyval.exp) = tree(yytext); }
#line 2998 "faustparser.cpp"
    break;

  case 185:
#line 611 "faustparser.y"
                                                                                                { (yyval.exp) = boxIPar((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3004 "faustparser.cpp"
    break;

  case 186:
#line 615 "faustparser.y"
                                                                                                { (yyval.exp) = boxISeq((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3010 "faustparser.cpp"
    break;

  case 187:
#line 619 "faustparser.y"
                                                                                                { (yyval.exp) = boxISum((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3016 "faustparser.cpp"
    break;

  case 188:
#line 623 "faustparser.y"
                                                                                                { (yyval.exp) = boxIProd((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3022 "faustparser.cpp"
    break;

  case 189:
#line 627 "faustparser.y"
                                                      { (yyval.exp) = boxInputs((yyvsp[-1].exp)); }
#line 3028 "faustparser.cpp"
    break;

  case 190:
#line 630 "faustparser.y"
                                                       { (yyval.exp) = boxOutputs((yyvsp[-1].exp)); }
#line 3034 "faustparser.cpp"
    break;

  case 191:
#line 633 "faustparser.y"
                                                { (yyval.exp) = boxOndemand((yyvsp[-1].exp)); }
#line 3040 "faustparser.cpp"
    break;

  case 192:
#line 639 "faustparser.y"
                                                                                                { (yyval.exp) = ffunction((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3046 "faustparser.cpp"
    break;

  case 193:
#line 643 "faustparser.y"
                                                { (yyval.exp) = boxFConst((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3052 "faustparser.cpp"
    break;

  case 194:
#line 646 "faustparser.y"
                                                { (yyval.exp) = boxFVar((yyvsp[-4].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3058 "faustparser.cpp"
    break;

  case 195:
#line 650 "faustparser.y"
                                                                { (yyval.exp) = boxButton((yyvsp[-1].exp)); }
#line 3064 "faustparser.cpp"
    break;

  case 196:
#line 653 "faustparser.y"
                                                                { (yyval.exp) = boxCheckbox((yyvsp[-1].exp)); }
#line 3070 "faustparser.cpp"
    break;

  case 197:
#line 657 "faustparser.y"
                                                                                                { (yyval.exp) = boxVSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3076 "faustparser.cpp"
    break;

  case 198:
#line 660 "faustparser.y"
                                                                                                { (yyval.exp) = boxHSlider((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3082 "faustparser.cpp"
    break;

  case 199:
#line 663 "faustparser.y"
                                                                                                { (yyval.exp) = boxNumEntry((yyvsp[-9].exp),(yyvsp[-7].exp),(yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3088 "faustparser.cpp"
    break;

  case 200:
#line 666 "faustparser.y"
                                                                                                { (yyval.exp) = boxVGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 3094 "faustparser.cpp"
    break;

  case 201:
#line 669 "faustparser.y"
                                                                                                { (yyval.exp) = boxHGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 3100 "faustparser.cpp"
    break;

  case 202:
#line 672 "faustparser.y"
                                                                                                { (yyval.exp) = boxTGroup((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 3106 "faustparser.cpp"
    break;

  case 203:
#line 676 "faustparser.y"
                                                                                                { (yyval.exp) = boxVBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3112 "faustparser.cpp"
    break;

  case 204:
#line 679 "faustparser.y"
                                                                                                { (yyval.exp) = boxHBargraph((yyvsp[-5].exp),(yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3118 "faustparser.cpp"
    break;

  case 205:
#line 682 "faustparser.y"
                                                                                                { (yyval.exp) = boxSoundfile((yyvsp[-3].exp),(yyvsp[-1].exp)); }
#line 3124 "faustparser.cpp"
    break;

  case 206:
#line 688 "faustparser.y"
                                                                    { (yyval.exp) = cons((yyvsp[-4].exp), cons(cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3130 "faustparser.cpp"
    break;

  case 207:
#line 689 "faustparser.y"
                                                            { (yyval.exp) = cons((yyvsp[-6].exp), cons(cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3136 "faustparser.cpp"
    break;

  case 208:
#line 690 "faustparser.y"
                                                                { (yyval.exp) = cons((yyvsp[-8].exp), cons(cons((yyvsp[-7].exp),cons((yyvsp[-5].exp),cons((yyvsp[-3].exp),gGlobal->nil))), (yyvsp[-1].exp))); }
#line 3142 "faustparser.cpp"
    break;

  case 209:
#line 692 "faustparser.y"
                                                            { (yyval.exp) = cons((yyvsp[-3].exp), cons(cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3148 "faustparser.cpp"
    break;

  case 210:
#line 693 "faustparser.y"
                                                            { (yyval.exp) = cons((yyvsp[-5].exp), cons(cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3154 "faustparser.cpp"
    break;

  case 211:
#line 694 "faustparser.y"
                                                                        { (yyval.exp) = cons((yyvsp[-7].exp), cons(cons((yyvsp[-6].exp),cons((yyvsp[-4].exp),cons((yyvsp[-2].exp),gGlobal->nil))), gGlobal->nil)); }
#line 3160 "faustparser.cpp"
    break;

  case 212:
#line 697 "faustparser.y"
                                                                                        { (yyval.exp) = tree(yytext); }
#line 3166 "faustparser.cpp"
    break;

  case 213:
#line 700 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3172 "faustparser.cpp"
    break;

  case 214:
#line 701 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-2].exp)); }
#line 3178 "faustparser.cpp"
    break;

  case 215:
#line 704 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),gGlobal->nil); }
#line 3184 "faustparser.cpp"
    break;

  case 216:
#line 705 "faustparser.y"
                                                                                { (yyval.exp) = cons((yyvsp[0].exp),(yyvsp[-1].exp)); }
#line 3190 "faustparser.cpp"
    break;

  case 217:
#line 709 "faustparser.y"
                                                                                                { (yyval.exp) = cons((yyvsp[-4].exp),(yyvsp[-1].exp)); }
#line 3196 "faustparser.cpp"
    break;

  case 218:
#line 712 "faustparser.y"
                                                        { (yyval.exp) = tree(0); }
#line 3202 "faustparser.cpp"
    break;

  case 219:
#line 713 "faustparser.y"
                                                                                        { (yyval.exp) = tree(1); }
#line 3208 "faustparser.cpp"
    break;


#line 3212 "faustparser.cpp"

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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
  return yyresult;
}
#line 716 "faustparser.y"


