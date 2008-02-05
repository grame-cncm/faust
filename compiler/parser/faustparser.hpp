/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     FVARIABLE = 290,
     BUTTON = 291,
     CHECKBOX = 292,
     VSLIDER = 293,
     HSLIDER = 294,
     NENTRY = 295,
     VGROUP = 296,
     HGROUP = 297,
     TGROUP = 298,
     HBARGRAPH = 299,
     VBARGRAPH = 300,
     ATTACH = 301,
     ACOS = 302,
     ASIN = 303,
     ATAN = 304,
     ATAN2 = 305,
     COS = 306,
     SIN = 307,
     TAN = 308,
     EXP = 309,
     LOG = 310,
     LOG10 = 311,
     POW = 312,
     SQRT = 313,
     ABS = 314,
     MIN = 315,
     MAX = 316,
     FMOD = 317,
     REMAINDER = 318,
     FLOOR = 319,
     CEIL = 320,
     RINT = 321,
     RDTBL = 322,
     RWTBL = 323,
     SELECT2 = 324,
     SELECT3 = 325,
     INT = 326,
     FLOAT = 327,
     LAMBDA = 328,
     WIRE = 329,
     CUT = 330,
     ENDDEF = 331,
     VIRG = 332,
     LPAR = 333,
     RPAR = 334,
     LBRAQ = 335,
     RBRAQ = 336,
     DEF = 337,
     IMPORT = 338,
     COMPONENT = 339,
     IPAR = 340,
     ISEQ = 341,
     ISUM = 342,
     IPROD = 343,
     STRING = 344,
     FSTRING = 345,
     IDENT = 346,
     EXTRA = 347,
     DECLARE = 348,
     CASE = 349,
     ARROW = 350
   };
#endif
/* Tokens.  */
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
#define FVARIABLE 290
#define BUTTON 291
#define CHECKBOX 292
#define VSLIDER 293
#define HSLIDER 294
#define NENTRY 295
#define VGROUP 296
#define HGROUP 297
#define TGROUP 298
#define HBARGRAPH 299
#define VBARGRAPH 300
#define ATTACH 301
#define ACOS 302
#define ASIN 303
#define ATAN 304
#define ATAN2 305
#define COS 306
#define SIN 307
#define TAN 308
#define EXP 309
#define LOG 310
#define LOG10 311
#define POW 312
#define SQRT 313
#define ABS 314
#define MIN 315
#define MAX 316
#define FMOD 317
#define REMAINDER 318
#define FLOOR 319
#define CEIL 320
#define RINT 321
#define RDTBL 322
#define RWTBL 323
#define SELECT2 324
#define SELECT3 325
#define INT 326
#define FLOAT 327
#define LAMBDA 328
#define WIRE 329
#define CUT 330
#define ENDDEF 331
#define VIRG 332
#define LPAR 333
#define RPAR 334
#define LBRAQ 335
#define RBRAQ 336
#define DEF 337
#define IMPORT 338
#define COMPONENT 339
#define IPAR 340
#define ISEQ 341
#define ISUM 342
#define IPROD 343
#define STRING 344
#define FSTRING 345
#define IDENT 346
#define EXTRA 347
#define DECLARE 348
#define CASE 349
#define ARROW 350




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 58 "parser/faustparser.y"
{
	CTree* 	exp;
}
/* Line 1489 of yacc.c.  */
#line 243 "parser/faustparser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

