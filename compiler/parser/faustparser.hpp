
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
     IPAR = 346,
     ISEQ = 347,
     ISUM = 348,
     IPROD = 349,
     STRING = 350,
     FSTRING = 351,
     IDENT = 352,
     EXTRA = 353,
     DECLARE = 354,
     CASE = 355,
     ARROW = 356,
     VECTORIZE = 357,
     SERIALIZE = 358,
     RATE = 359,
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



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 78 "parser/faustparser.y"

	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;



/* Line 1676 of yacc.c  */
#line 185 "parser/faustparser.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


