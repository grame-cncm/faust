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
    BDOC = 360,
    EDOC = 361,
    BEQN = 362,
    EEQN = 363,
    BDGM = 364,
    EDGM = 365,
    BLST = 366,
    ELST = 367,
    BMETADATA = 368,
    EMETADATA = 369,
    DOCCHAR = 370,
    NOTICE = 371,
    LISTING = 372,
    LSTTRUE = 373,
    LSTFALSE = 374,
    LSTDEPENDENCIES = 375,
    LSTMDOCTAGS = 376,
    LSTDISTRIBUTED = 377,
    LSTEQ = 378,
    LSTQ = 379
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 71 "parser/faustparser.y" /* yacc.c:1909  */

	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;

#line 186 "parser/faustparser.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_FAUSTPARSER_HPP_INCLUDED  */
