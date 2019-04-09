/* A Bison parser, made by GNU Bison 3.2.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
    STRING = 357,
    FSTRING = 358,
    IDENT = 359,
    EXTRA = 360,
    DECLARE = 361,
    CASE = 362,
    ARROW = 363,
    BDOC = 364,
    EDOC = 365,
    BEQN = 366,
    EEQN = 367,
    BDGM = 368,
    EDGM = 369,
    BLST = 370,
    ELST = 371,
    BMETADATA = 372,
    EMETADATA = 373,
    DOCCHAR = 374,
    NOTICE = 375,
    LISTING = 376,
    LSTTRUE = 377,
    LSTFALSE = 378,
    LSTDEPENDENCIES = 379,
    LSTMDOCTAGS = 380,
    LSTDISTRIBUTED = 381,
    LSTEQ = 382,
    LSTQ = 383
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 73 "faustparser.y" /* yacc.c:1906  */

	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;

#line 193 "faustparser.hpp" /* yacc.c:1906  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_FAUSTPARSER_HPP_INCLUDED  */
