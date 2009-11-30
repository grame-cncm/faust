
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
     DEF = 338,
     IMPORT = 339,
     COMPONENT = 340,
     LIBRARY = 341,
     ENVIRONMENT = 342,
     IPAR = 343,
     ISEQ = 344,
     ISUM = 345,
     IPROD = 346,
     STRING = 347,
     FSTRING = 348,
     IDENT = 349,
     EXTRA = 350,
     DECLARE = 351,
     CASE = 352,
     ARROW = 353,
     BDOC = 354,
     EDOC = 355,
     BEQN = 356,
     EEQN = 357,
     BDGM = 358,
     EDGM = 359,
     DOCCHAR = 360,
     NOTICE = 361,
     LISTING = 362
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 64 "parser/faustparser.y"

	CTree* 	exp;
	char* str;



/* Line 1676 of yacc.c  */
#line 166 "parser/faustparser.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


