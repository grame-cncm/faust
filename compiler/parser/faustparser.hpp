/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSER_FAUSTPARSER_HPP_INCLUDED
# define YY_YY_PARSER_FAUSTPARSER_HPP_INCLUDED
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
    SPLIT = 259,
    MIX = 260,
    SEQ = 261,
    PAR = 262,
    REC = 263,
    LT = 264,
    LE = 265,
    EQ = 266,
    GT = 267,
    GE = 268,
    NE = 269,
    ADD = 270,
    SUB = 271,
    OR = 272,
    MUL = 273,
    DIV = 274,
    MOD = 275,
    AND = 276,
    XOR = 277,
    LSH = 278,
    RSH = 279,
    POWOP = 280,
    FDELAY = 281,
    DELAY1 = 282,
    APPL = 283,
    DOT = 284,
    HASH = 285,
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
    ATTACH = 303,
    ACOS = 304,
    ASIN = 305,
    ATAN = 306,
    ATAN2 = 307,
    COS = 308,
    SIN = 309,
    TAN = 310,
    EXP = 311,
    LOG = 312,
    LOG10 = 313,
    POWFUN = 314,
    SQRT = 315,
    ABS = 316,
    MIN = 317,
    MAX = 318,
    FMOD = 319,
    REMAINDER = 320,
    FLOOR = 321,
    CEIL = 322,
    RINT = 323,
    RDTBL = 324,
    RWTBL = 325,
    SELECT2 = 326,
    SELECT3 = 327,
    INT = 328,
    FLOAT = 329,
    LAMBDA = 330,
    WIRE = 331,
    CUT = 332,
    ENDDEF = 333,
    VIRG = 334,
    LPAR = 335,
    RPAR = 336,
    LBRAQ = 337,
    RBRAQ = 338,
    LCROC = 339,
    RCROC = 340,
    DEF = 341,
    IMPORT = 342,
    COMPONENT = 343,
    LIBRARY = 344,
    ENVIRONMENT = 345,
    WAVEFORM = 346,
    IPAR = 347,
    ISEQ = 348,
    ISUM = 349,
    IPROD = 350,
    INPUTS = 351,
    OUTPUTS = 352,
    STRING = 353,
    FSTRING = 354,
    IDENT = 355,
    EXTRA = 356,
    DECLARE = 357,
    CASE = 358,
    ARROW = 359,
    VECTORIZE = 360,
    SERIALIZE = 361,
    RATE = 362,
    UPSAMPLE = 363,
    DOWNSAMPLE = 364,
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
#line 78 "parser/faustparser.y" /* yacc.c:1909  */

	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;

#line 191 "parser/faustparser.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_FAUSTPARSER_HPP_INCLUDED  */
