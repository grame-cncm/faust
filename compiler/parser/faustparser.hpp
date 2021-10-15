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
     LETREC = 259,
     MIX = 260,
     SPLIT = 261,
     SEQ = 262,
     PAR = 263,
     REC = 264,
     NE = 265,
     GE = 266,
     GT = 267,
     EQ = 268,
     LE = 269,
     LT = 270,
     OR = 271,
     SUB = 272,
     ADD = 273,
     RSH = 274,
     LSH = 275,
     XOR = 276,
     AND = 277,
     MOD = 278,
     DIV = 279,
     MUL = 280,
     POWOP = 281,
     FDELAY = 282,
     DELAY1 = 283,
     DOT = 284,
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
     SOUNDFILE = 302,
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
     ROUTE = 347,
     ENABLE = 348,
     CONTROL = 349,
     IPAR = 350,
     ISEQ = 351,
     ISUM = 352,
     IPROD = 353,
     INPUTS = 354,
     OUTPUTS = 355,
     STRING = 356,
     FSTRING = 357,
     IDENT = 358,
     EXTRA = 359,
     DECLARE = 360,
     CASE = 361,
     ARROW = 362,
     ASSERTBOUNDS = 363,
     LOWEST = 364,
     HIGHEST = 365,
     FLOATMODE = 366,
     DOUBLEMODE = 367,
     QUADMODE = 368,
     FIXEDPOINTMODE = 369,
     BDOC = 370,
     EDOC = 371,
     BEQN = 372,
     EEQN = 373,
     BDGM = 374,
     EDGM = 375,
     BLST = 376,
     ELST = 377,
     BMETADATA = 378,
     EMETADATA = 379,
     DOCCHAR = 380,
     NOTICE = 381,
     LISTING = 382,
     LSTTRUE = 383,
     LSTFALSE = 384,
     LSTDEPENDENCIES = 385,
     LSTMDOCTAGS = 386,
     LSTDISTRIBUTED = 387,
     LSTEQ = 388,
     LSTQ = 389
   };
#endif
/* Tokens.  */
#define WITH 258
#define LETREC 259
#define MIX 260
#define SPLIT 261
#define SEQ 262
#define PAR 263
#define REC 264
#define NE 265
#define GE 266
#define GT 267
#define EQ 268
#define LE 269
#define LT 270
#define OR 271
#define SUB 272
#define ADD 273
#define RSH 274
#define LSH 275
#define XOR 276
#define AND 277
#define MOD 278
#define DIV 279
#define MUL 280
#define POWOP 281
#define FDELAY 282
#define DELAY1 283
#define DOT 284
#define MEM 285
#define PREFIX 286
#define INTCAST 287
#define FLOATCAST 288
#define FFUNCTION 289
#define FCONSTANT 290
#define FVARIABLE 291
#define BUTTON 292
#define CHECKBOX 293
#define VSLIDER 294
#define HSLIDER 295
#define NENTRY 296
#define VGROUP 297
#define HGROUP 298
#define TGROUP 299
#define HBARGRAPH 300
#define VBARGRAPH 301
#define SOUNDFILE 302
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
#define ROUTE 347
#define ENABLE 348
#define CONTROL 349
#define IPAR 350
#define ISEQ 351
#define ISUM 352
#define IPROD 353
#define INPUTS 354
#define OUTPUTS 355
#define STRING 356
#define FSTRING 357
#define IDENT 358
#define EXTRA 359
#define DECLARE 360
#define CASE 361
#define ARROW 362
#define ASSERTBOUNDS 363
#define LOWEST 364
#define HIGHEST 365
#define FLOATMODE 366
#define DOUBLEMODE 367
#define QUADMODE 368
#define FIXEDPOINTMODE 369
#define BDOC 370
#define EDOC 371
#define BEQN 372
#define EEQN 373
#define BDGM 374
#define EDGM 375
#define BLST 376
#define ELST 377
#define BMETADATA 378
#define EMETADATA 379
#define DOCCHAR 380
#define NOTICE 381
#define LISTING 382
#define LSTTRUE 383
#define LSTFALSE 384
#define LSTDEPENDENCIES 385
#define LSTMDOCTAGS 386
#define LSTDISTRIBUTED 387
#define LSTEQ 388
#define LSTQ 389




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 80 "faustparser.y"
{
	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;
	int numvariant;
}
/* Line 1529 of yacc.c.  */
#line 325 "faustparser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

