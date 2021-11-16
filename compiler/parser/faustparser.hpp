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
    APPL = 282,                    /* APPL  */
    MEM = 283,                     /* MEM  */
    PREFIX = 284,                  /* PREFIX  */
    INTCAST = 285,                 /* INTCAST  */
    FLOATCAST = 286,               /* FLOATCAST  */
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
    RDTBL = 322,                   /* RDTBL  */
    RWTBL = 323,                   /* RWTBL  */
    SELECT2 = 324,                 /* SELECT2  */
    SELECT3 = 325,                 /* SELECT3  */
    INT = 326,                     /* INT  */
    FLOAT = 327,                   /* FLOAT  */
    LAMBDA = 328,                  /* LAMBDA  */
    DOT = 329,                     /* DOT  */
    WIRE = 330,                    /* WIRE  */
    CUT = 331,                     /* CUT  */
    ENDDEF = 332,                  /* ENDDEF  */
    VIRG = 333,                    /* VIRG  */
    LPAR = 334,                    /* LPAR  */
    RPAR = 335,                    /* RPAR  */
    LBRAQ = 336,                   /* LBRAQ  */
    RBRAQ = 337,                   /* RBRAQ  */
    LCROC = 338,                   /* LCROC  */
    RCROC = 339,                   /* RCROC  */
    WITH = 340,                    /* WITH  */
    LETREC = 341,                  /* LETREC  */
    DEF = 342,                     /* DEF  */
    IMPORT = 343,                  /* IMPORT  */
    COMPONENT = 344,               /* COMPONENT  */
    LIBRARY = 345,                 /* LIBRARY  */
    ENVIRONMENT = 346,             /* ENVIRONMENT  */
    WAVEFORM = 347,                /* WAVEFORM  */
    ROUTE = 348,                   /* ROUTE  */
    ENABLE = 349,                  /* ENABLE  */
    CONTROL = 350,                 /* CONTROL  */
    IPAR = 351,                    /* IPAR  */
    ISEQ = 352,                    /* ISEQ  */
    ISUM = 353,                    /* ISUM  */
    IPROD = 354,                   /* IPROD  */
    INPUTS = 355,                  /* INPUTS  */
    OUTPUTS = 356,                 /* OUTPUTS  */
    ONDEMAND = 357,                /* ONDEMAND  */
    STRING = 358,                  /* STRING  */
    FSTRING = 359,                 /* FSTRING  */
    IDENT = 360,                   /* IDENT  */
    EXTRA = 361,                   /* EXTRA  */
    DECLARE = 362,                 /* DECLARE  */
    CASE = 363,                    /* CASE  */
    ARROW = 364,                   /* ARROW  */
    BDOC = 365,                    /* BDOC  */
    EDOC = 366,                    /* EDOC  */
    BEQN = 367,                    /* BEQN  */
    EEQN = 368,                    /* EEQN  */
    BDGM = 369,                    /* BDGM  */
    EDGM = 370,                    /* EDGM  */
    BLST = 371,                    /* BLST  */
    ELST = 372,                    /* ELST  */
    BMETADATA = 373,               /* BMETADATA  */
    EMETADATA = 374,               /* EMETADATA  */
    DOCCHAR = 375,                 /* DOCCHAR  */
    NOTICE = 376,                  /* NOTICE  */
    LISTING = 377,                 /* LISTING  */
    LSTTRUE = 378,                 /* LSTTRUE  */
    LSTFALSE = 379,                /* LSTFALSE  */
    LSTDEPENDENCIES = 380,         /* LSTDEPENDENCIES  */
    LSTMDOCTAGS = 381,             /* LSTMDOCTAGS  */
    LSTDISTRIBUTED = 382,          /* LSTDISTRIBUTED  */
    LSTEQ = 383,                   /* LSTEQ  */
    LSTQ = 384                     /* LSTQ  */
  };
  typedef enum yytokentype yytoken_kind_t;
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

#line 200 "faustparser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_FAUSTPARSER_HPP_INCLUDED  */
