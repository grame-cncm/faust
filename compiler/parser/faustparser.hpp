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
     NOTYPECAST = 289,
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
     WHERE = 342,
     DEF = 343,
     IMPORT = 344,
     COMPONENT = 345,
     LIBRARY = 346,
     ENVIRONMENT = 347,
     WAVEFORM = 348,
     ROUTE = 349,
     ENABLE = 350,
     CONTROL = 351,
     IPAR = 352,
     ISEQ = 353,
     ISUM = 354,
     IPROD = 355,
     INPUTS = 356,
     OUTPUTS = 357,
     STRING = 358,
     FSTRING = 359,
     IDENT = 360,
     EXTRA = 361,
     DECLARE = 362,
     CASE = 363,
     ARROW = 364,
     ASSERTBOUNDS = 365,
     LOWEST = 366,
     HIGHEST = 367,
     FLOATMODE = 368,
     DOUBLEMODE = 369,
     QUADMODE = 370,
     FIXEDPOINTMODE = 371,
     BDOC = 372,
     EDOC = 373,
     BEQN = 374,
     EEQN = 375,
     BDGM = 376,
     EDGM = 377,
     BLST = 378,
     ELST = 379,
     BMETADATA = 380,
     EMETADATA = 381,
     DOCCHAR = 382,
     NOTICE = 383,
     LISTING = 384,
     LSTTRUE = 385,
     LSTFALSE = 386,
     LSTDEPENDENCIES = 387,
     LSTMDOCTAGS = 388,
     LSTDISTRIBUTED = 389,
     LSTEQ = 390,
     LSTQ = 391
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
#define NOTYPECAST 289
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
#define SOUNDFILE 303
#define ATTACH 304
#define ACOS 305
#define ASIN 306
#define ATAN 307
#define ATAN2 308
#define COS 309
#define SIN 310
#define TAN 311
#define EXP 312
#define LOG 313
#define LOG10 314
#define POWFUN 315
#define SQRT 316
#define ABS 317
#define MIN 318
#define MAX 319
#define FMOD 320
#define REMAINDER 321
#define FLOOR 322
#define CEIL 323
#define RINT 324
#define RDTBL 325
#define RWTBL 326
#define SELECT2 327
#define SELECT3 328
#define INT 329
#define FLOAT 330
#define LAMBDA 331
#define WIRE 332
#define CUT 333
#define ENDDEF 334
#define VIRG 335
#define LPAR 336
#define RPAR 337
#define LBRAQ 338
#define RBRAQ 339
#define LCROC 340
#define RCROC 341
#define WHERE 342
#define DEF 343
#define IMPORT 344
#define COMPONENT 345
#define LIBRARY 346
#define ENVIRONMENT 347
#define WAVEFORM 348
#define ROUTE 349
#define ENABLE 350
#define CONTROL 351
#define IPAR 352
#define ISEQ 353
#define ISUM 354
#define IPROD 355
#define INPUTS 356
#define OUTPUTS 357
#define STRING 358
#define FSTRING 359
#define IDENT 360
#define EXTRA 361
#define DECLARE 362
#define CASE 363
#define ARROW 364
#define ASSERTBOUNDS 365
#define LOWEST 366
#define HIGHEST 367
#define FLOATMODE 368
#define DOUBLEMODE 369
#define QUADMODE 370
#define FIXEDPOINTMODE 371
#define BDOC 372
#define EDOC 373
#define BEQN 374
#define EEQN 375
#define BDGM 376
#define EDGM 377
#define BLST 378
#define ELST 379
#define BMETADATA 380
#define EMETADATA 381
#define DOCCHAR 382
#define NOTICE 383
#define LISTING 384
#define LSTTRUE 385
#define LSTFALSE 386
#define LSTDEPENDENCIES 387
#define LSTMDOCTAGS 388
#define LSTDISTRIBUTED 389
#define LSTEQ 390
#define LSTQ 391




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 96 "faustparser.y"
{
	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;
	int numvariant;
}
/* Line 1529 of yacc.c.  */
#line 329 "faustparser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

