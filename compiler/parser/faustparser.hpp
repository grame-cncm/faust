/* A Bison parser, made by GNU Bison 3.7.6.  */

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

#ifndef YY_YY_FAUSTPARSER_HPP_INCLUDED
# define YY_YY_FAUSTPARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
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
    FFUNCTION = 286,               /* FFUNCTION  */
    FCONSTANT = 287,               /* FCONSTANT  */
    FVARIABLE = 288,               /* FVARIABLE  */
    BUTTON = 289,                  /* BUTTON  */
    CHECKBOX = 290,                /* CHECKBOX  */
    VSLIDER = 291,                 /* VSLIDER  */
    HSLIDER = 292,                 /* HSLIDER  */
    NENTRY = 293,                  /* NENTRY  */
    VGROUP = 294,                  /* VGROUP  */
    HGROUP = 295,                  /* HGROUP  */
    TGROUP = 296,                  /* TGROUP  */
    HBARGRAPH = 297,               /* HBARGRAPH  */
    VBARGRAPH = 298,               /* VBARGRAPH  */
    SOUNDFILE = 299,               /* SOUNDFILE  */
    ATTACH = 300,                  /* ATTACH  */
    ACOS = 301,                    /* ACOS  */
    ASIN = 302,                    /* ASIN  */
    ATAN = 303,                    /* ATAN  */
    ATAN2 = 304,                   /* ATAN2  */
    COS = 305,                     /* COS  */
    SIN = 306,                     /* SIN  */
    TAN = 307,                     /* TAN  */
    EXP = 308,                     /* EXP  */
    LOG = 309,                     /* LOG  */
    LOG10 = 310,                   /* LOG10  */
    POWFUN = 311,                  /* POWFUN  */
    SQRT = 312,                    /* SQRT  */
    ABS = 313,                     /* ABS  */
    MIN = 314,                     /* MIN  */
    MAX = 315,                     /* MAX  */
    FMOD = 316,                    /* FMOD  */
    REMAINDER = 317,               /* REMAINDER  */
    FLOOR = 318,                   /* FLOOR  */
    CEIL = 319,                    /* CEIL  */
    RINT = 320,                    /* RINT  */
    RDTBL = 321,                   /* RDTBL  */
    RWTBL = 322,                   /* RWTBL  */
    SELECT2 = 323,                 /* SELECT2  */
    SELECT3 = 324,                 /* SELECT3  */
    INT = 325,                     /* INT  */
    FLOAT = 326,                   /* FLOAT  */
    LAMBDA = 327,                  /* LAMBDA  */
    DOT = 328,                     /* DOT  */
    WIRE = 329,                    /* WIRE  */
    CUT = 330,                     /* CUT  */
    ENDDEF = 331,                  /* ENDDEF  */
    VIRG = 332,                    /* VIRG  */
    LPAR = 333,                    /* LPAR  */
    RPAR = 334,                    /* RPAR  */
    LBRAQ = 335,                   /* LBRAQ  */
    RBRAQ = 336,                   /* RBRAQ  */
    LCROC = 337,                   /* LCROC  */
    RCROC = 338,                   /* RCROC  */
    WITH = 339,                    /* WITH  */
    LETREC = 340,                  /* LETREC  */
    DEF = 341,                     /* DEF  */
    IMPORT = 342,                  /* IMPORT  */
    COMPONENT = 343,               /* COMPONENT  */
    LIBRARY = 344,                 /* LIBRARY  */
    ENVIRONMENT = 345,             /* ENVIRONMENT  */
    WAVEFORM = 346,                /* WAVEFORM  */
    ROUTE = 347,                   /* ROUTE  */
    ENABLE = 348,                  /* ENABLE  */
    CONTROL = 349,                 /* CONTROL  */
    IPAR = 350,                    /* IPAR  */
    ISEQ = 351,                    /* ISEQ  */
    ISUM = 352,                    /* ISUM  */
    IPROD = 353,                   /* IPROD  */
    INPUTS = 354,                  /* INPUTS  */
    OUTPUTS = 355,                 /* OUTPUTS  */
    STRING = 356,                  /* STRING  */
    FSTRING = 357,                 /* FSTRING  */
    IDENT = 358,                   /* IDENT  */
    EXTRA = 359,                   /* EXTRA  */
    DECLARE = 360,                 /* DECLARE  */
    CASE = 361,                    /* CASE  */
    ARROW = 362,                   /* ARROW  */
    FLOATMODE = 363,               /* FLOATMODE  */
    DOUBLEMODE = 364,              /* DOUBLEMODE  */
    QUADMODE = 365,                /* QUADMODE  */
    FIXEDPOINTMODE = 366,          /* FIXEDPOINTMODE  */
    BDOC = 367,                    /* BDOC  */
    EDOC = 368,                    /* EDOC  */
    BEQN = 369,                    /* BEQN  */
    EEQN = 370,                    /* EEQN  */
    BDGM = 371,                    /* BDGM  */
    EDGM = 372,                    /* EDGM  */
    BLST = 373,                    /* BLST  */
    ELST = 374,                    /* ELST  */
    BMETADATA = 375,               /* BMETADATA  */
    EMETADATA = 376,               /* EMETADATA  */
    DOCCHAR = 377,                 /* DOCCHAR  */
    NOTICE = 378,                  /* NOTICE  */
    LISTING = 379,                 /* LISTING  */
    LSTTRUE = 380,                 /* LSTTRUE  */
    LSTFALSE = 381,                /* LSTFALSE  */
    LSTDEPENDENCIES = 382,         /* LSTDEPENDENCIES  */
    LSTMDOCTAGS = 383,             /* LSTMDOCTAGS  */
    LSTDISTRIBUTED = 384,          /* LSTDISTRIBUTED  */
    LSTEQ = 385,                   /* LSTEQ  */
    LSTQ = 386                     /* LSTQ  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 81 "faustparser.y"

	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;
	int numvariant;

#line 203 "faustparser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_FAUSTPARSER_HPP_INCLUDED  */
