/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_FAUST_FAUSTPARSER_HPP_INCLUDED
# define YY_FAUST_FAUSTPARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int FAUSTdebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SPLIT = 258,                   /* SPLIT  */
    MIX = 259,                     /* MIX  */
    SEQ = 260,                     /* SEQ  */
    PAR = 261,                     /* PAR  */
    REC = 262,                     /* REC  */
    LT = 263,                      /* LT  */
    LE = 264,                      /* LE  */
    EQ = 265,                      /* EQ  */
    GT = 266,                      /* GT  */
    GE = 267,                      /* GE  */
    NE = 268,                      /* NE  */
    ADD = 269,                     /* ADD  */
    SUB = 270,                     /* SUB  */
    OR = 271,                      /* OR  */
    MUL = 272,                     /* MUL  */
    DIV = 273,                     /* DIV  */
    MOD = 274,                     /* MOD  */
    AND = 275,                     /* AND  */
    XOR = 276,                     /* XOR  */
    LSH = 277,                     /* LSH  */
    RSH = 278,                     /* RSH  */
    POWOP = 279,                   /* POWOP  */
    FDELAY = 280,                  /* FDELAY  */
    DELAY1 = 281,                  /* DELAY1  */
    MEM = 282,                     /* MEM  */
    PREFIX = 283,                  /* PREFIX  */
    INTCAST = 284,                 /* INTCAST  */
    FLOATCAST = 285,               /* FLOATCAST  */
    NOTYPECAST = 286,              /* NOTYPECAST  */
    FFUNCTION = 287,               /* FFUNCTION  */
    FCONSTANT = 288,               /* FCONSTANT  */
    FVARIABLE = 289,               /* FVARIABLE  */
    BUTTON = 290,                  /* BUTTON  */
    CHECKBOX = 291,                /* CHECKBOX  */
    VSLIDER = 292,                 /* VSLIDER  */
    HSLIDER = 293,                 /* HSLIDER  */
    NENTRY = 294,                  /* NENTRY  */
    VGROUP = 295,                  /* VGROUP  */
    HGROUP = 296,                  /* HGROUP  */
    TGROUP = 297,                  /* TGROUP  */
    HBARGRAPH = 298,               /* HBARGRAPH  */
    VBARGRAPH = 299,               /* VBARGRAPH  */
    SOUNDFILE = 300,               /* SOUNDFILE  */
    ATTACH = 301,                  /* ATTACH  */
    ACOS = 302,                    /* ACOS  */
    ASIN = 303,                    /* ASIN  */
    ATAN = 304,                    /* ATAN  */
    ATAN2 = 305,                   /* ATAN2  */
    COS = 306,                     /* COS  */
    SIN = 307,                     /* SIN  */
    TAN = 308,                     /* TAN  */
    EXP = 309,                     /* EXP  */
    LOG = 310,                     /* LOG  */
    LOG10 = 311,                   /* LOG10  */
    POWFUN = 312,                  /* POWFUN  */
    SQRT = 313,                    /* SQRT  */
    ABS = 314,                     /* ABS  */
    MIN = 315,                     /* MIN  */
    MAX = 316,                     /* MAX  */
    FMOD = 317,                    /* FMOD  */
    REMAINDER = 318,               /* REMAINDER  */
    FLOOR = 319,                   /* FLOOR  */
    CEIL = 320,                    /* CEIL  */
    RINT = 321,                    /* RINT  */
    ROUND = 322,                   /* ROUND  */
    RDTBL = 323,                   /* RDTBL  */
    RWTBL = 324,                   /* RWTBL  */
    SELECT2 = 325,                 /* SELECT2  */
    SELECT3 = 326,                 /* SELECT3  */
    INT = 327,                     /* INT  */
    FLOAT = 328,                   /* FLOAT  */
    MODULATE = 329,                /* MODULATE  */
    LAMBDA = 330,                  /* LAMBDA  */
    DOT = 331,                     /* DOT  */
    WIRE = 332,                    /* WIRE  */
    CUT = 333,                     /* CUT  */
    ENDDEF = 334,                  /* ENDDEF  */
    VIRG = 335,                    /* VIRG  */
    LPAR = 336,                    /* LPAR  */
    RPAR = 337,                    /* RPAR  */
    LBRAQ = 338,                   /* LBRAQ  */
    RBRAQ = 339,                   /* RBRAQ  */
    LCROC = 340,                   /* LCROC  */
    RCROC = 341,                   /* RCROC  */
    WITH = 342,                    /* WITH  */
    LETREC = 343,                  /* LETREC  */
    WHERE = 344,                   /* WHERE  */
    DEF = 345,                     /* DEF  */
    LAPPLY = 346,                  /* LAPPLY  */
    IMPORT = 347,                  /* IMPORT  */
    COMPONENT = 348,               /* COMPONENT  */
    LIBRARY = 349,                 /* LIBRARY  */
    ENVIRONMENT = 350,             /* ENVIRONMENT  */
    WAVEFORM = 351,                /* WAVEFORM  */
    ROUTE = 352,                   /* ROUTE  */
    ENABLE = 353,                  /* ENABLE  */
    CONTROL = 354,                 /* CONTROL  */
    IPAR = 355,                    /* IPAR  */
    ISEQ = 356,                    /* ISEQ  */
    ISUM = 357,                    /* ISUM  */
    IPROD = 358,                   /* IPROD  */
    INPUTS = 359,                  /* INPUTS  */
    OUTPUTS = 360,                 /* OUTPUTS  */
    STRING = 361,                  /* STRING  */
    FSTRING = 362,                 /* FSTRING  */
    IDENT = 363,                   /* IDENT  */
    EXTRA = 364,                   /* EXTRA  */
    DECLARE = 365,                 /* DECLARE  */
    CASE = 366,                    /* CASE  */
    ARROW = 367,                   /* ARROW  */
    ASSERTBOUNDS = 368,            /* ASSERTBOUNDS  */
    LOWEST = 369,                  /* LOWEST  */
    HIGHEST = 370,                 /* HIGHEST  */
    FLOATMODE = 371,               /* FLOATMODE  */
    DOUBLEMODE = 372,              /* DOUBLEMODE  */
    QUADMODE = 373,                /* QUADMODE  */
    FIXEDPOINTMODE = 374,          /* FIXEDPOINTMODE  */
    BDOC = 375,                    /* BDOC  */
    EDOC = 376,                    /* EDOC  */
    BEQN = 377,                    /* BEQN  */
    EEQN = 378,                    /* EEQN  */
    BDGM = 379,                    /* BDGM  */
    EDGM = 380,                    /* EDGM  */
    BLST = 381,                    /* BLST  */
    ELST = 382,                    /* ELST  */
    BMETADATA = 383,               /* BMETADATA  */
    EMETADATA = 384,               /* EMETADATA  */
    DOCCHAR = 385,                 /* DOCCHAR  */
    NOTICE = 386,                  /* NOTICE  */
    LISTING = 387,                 /* LISTING  */
    LSTTRUE = 388,                 /* LSTTRUE  */
    LSTFALSE = 389,                /* LSTFALSE  */
    LSTDEPENDENCIES = 390,         /* LSTDEPENDENCIES  */
    LSTMDOCTAGS = 391,             /* LSTMDOCTAGS  */
    LSTDISTRIBUTED = 392,          /* LSTDISTRIBUTED  */
    LSTEQ = 393,                   /* LSTEQ  */
    LSTQ = 394                     /* LSTQ  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 96 "faustparser.y"

    CTree*     exp;
    char* str;
    std::string* cppstr;
    bool b;
    int numvariant;

#line 211 "faustparser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE FAUSTlval;


int FAUSTparse (void);


#endif /* !YY_FAUST_FAUSTPARSER_HPP_INCLUDED  */
