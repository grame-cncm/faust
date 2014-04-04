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
#define POWOP 280
#define FDELAY 281
#define DELAY1 282
#define DOT 283
#define APPL 284
#define HASH 285
#define MEM 286
#define PREFIX 287
#define INTCAST 288
#define FLOATCAST 289
#define FFUNCTION 290
#define FCONSTANT 291
#define FVARIABLE 292
#define BUTTON 293
#define CHECKBOX 294
#define VSLIDER 295
#define HSLIDER 296
#define NENTRY 297
#define VGROUP 298
#define HGROUP 299
#define TGROUP 300
#define HBARGRAPH 301
#define VBARGRAPH 302
#define ATTACH 303
#define ACOS 304
#define ASIN 305
#define ATAN 306
#define ATAN2 307
#define COS 308
#define SIN 309
#define TAN 310
#define EXP 311
#define LOG 312
#define LOG10 313
#define POWFUN 314
#define SQRT 315
#define ABS 316
#define MIN 317
#define MAX 318
#define FMOD 319
#define REMAINDER 320
#define FLOOR 321
#define CEIL 322
#define RINT 323
#define RDTBL 324
#define RWTBL 325
#define SELECT2 326
#define SELECT3 327
#define INT 328
#define FLOAT 329
#define LAMBDA 330
#define WIRE 331
#define CUT 332
#define ENDDEF 333
#define VIRG 334
#define LPAR 335
#define RPAR 336
#define LBRAQ 337
#define RBRAQ 338
#define LCROC 339
#define RCROC 340
#define DEF 341
#define IMPORT 342
#define COMPONENT 343
#define LIBRARY 344
#define ENVIRONMENT 345
#define WAVEFORM 346
#define IPAR 347
#define ISEQ 348
#define ISUM 349
#define IPROD 350
#define INPUTS 351
#define OUTPUTS 352
#define STRING 353
#define FSTRING 354
#define IDENT 355
#define EXTRA 356
#define DECLARE 357
#define CASE 358
#define ARROW 359
#define VECTORIZE 360
#define SERIALIZE 361
#define RATE 362
#define UPSAMPLE 363
#define DOWNSAMPLE 364
#define BDOC 365
#define EDOC 366
#define BEQN 367
#define EEQN 368
#define BDGM 369
#define EDGM 370
#define BLST 371
#define ELST 372
#define BMETADATA 373
#define EMETADATA 374
#define DOCCHAR 375
#define NOTICE 376
#define LISTING 377
#define LSTTRUE 378
#define LSTFALSE 379
#define LSTDEPENDENCIES 380
#define LSTMDOCTAGS 381
#define LSTDISTRIBUTED 382
#define LSTEQ 383
#define LSTQ 384




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 78 "parser/faustparser.y"
{
	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;
}
/* Line 1529 of yacc.c.  */
#line 314 "parser/faustparser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

