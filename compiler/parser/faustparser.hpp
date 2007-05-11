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
     BUTTON = 290,
     CHECKBOX = 291,
     VSLIDER = 292,
     HSLIDER = 293,
     NENTRY = 294,
     VGROUP = 295,
     HGROUP = 296,
     TGROUP = 297,
     HBARGRAPH = 298,
     VBARGRAPH = 299,
     ATTACH = 300,
     ACOS = 301,
     ASIN = 302,
     ATAN = 303,
     ATAN2 = 304,
     COS = 305,
     SIN = 306,
     TAN = 307,
     EXP = 308,
     LOG = 309,
     LOG10 = 310,
     POW = 311,
     SQRT = 312,
     ABS = 313,
     MIN = 314,
     MAX = 315,
     FMOD = 316,
     REMAINDER = 317,
     FLOOR = 318,
     CEIL = 319,
     RINT = 320,
     RDTBL = 321,
     RWTBL = 322,
     SELECT2 = 323,
     SELECT3 = 324,
     INT = 325,
     FLOAT = 326,
     LAMBDA = 327,
     WIRE = 328,
     CUT = 329,
     ENDDEF = 330,
     VIRG = 331,
     LPAR = 332,
     RPAR = 333,
     LBRAQ = 334,
     RBRAQ = 335,
     DEF = 336,
     IMPORT = 337,
     COMPONENT = 338,
     IPAR = 339,
     ISEQ = 340,
     ISUM = 341,
     IPROD = 342,
     STRING = 343,
     FSTRING = 344,
     IDENT = 345,
     EXTRA = 346,
     DECLARE = 347,
     NAMEPROP = 348,
     AUTHORPROP = 349,
     COPYRIGHTPROP = 350,
     VERSIONPROP = 351,
     LICENSEPROP = 352,
     CASE = 353,
     ARROW = 354
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
#define BUTTON 290
#define CHECKBOX 291
#define VSLIDER 292
#define HSLIDER 293
#define NENTRY 294
#define VGROUP 295
#define HGROUP 296
#define TGROUP 297
#define HBARGRAPH 298
#define VBARGRAPH 299
#define ATTACH 300
#define ACOS 301
#define ASIN 302
#define ATAN 303
#define ATAN2 304
#define COS 305
#define SIN 306
#define TAN 307
#define EXP 308
#define LOG 309
#define LOG10 310
#define POW 311
#define SQRT 312
#define ABS 313
#define MIN 314
#define MAX 315
#define FMOD 316
#define REMAINDER 317
#define FLOOR 318
#define CEIL 319
#define RINT 320
#define RDTBL 321
#define RWTBL 322
#define SELECT2 323
#define SELECT3 324
#define INT 325
#define FLOAT 326
#define LAMBDA 327
#define WIRE 328
#define CUT 329
#define ENDDEF 330
#define VIRG 331
#define LPAR 332
#define RPAR 333
#define LBRAQ 334
#define RBRAQ 335
#define DEF 336
#define IMPORT 337
#define COMPONENT 338
#define IPAR 339
#define ISEQ 340
#define ISUM 341
#define IPROD 342
#define STRING 343
#define FSTRING 344
#define IDENT 345
#define EXTRA 346
#define DECLARE 347
#define NAMEPROP 348
#define AUTHORPROP 349
#define COPYRIGHTPROP 350
#define VERSIONPROP 351
#define LICENSEPROP 352
#define CASE 353
#define ARROW 354




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 62 "parser/faustparser.y"
{
	CTree* 	exp;
}
/* Line 1529 of yacc.c.  */
#line 251 "parser/faustparser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

