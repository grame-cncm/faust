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
     ROUND = 325,
     RDTBL = 326,
     RWTBL = 327,
     SELECT2 = 328,
     SELECT3 = 329,
     INT = 330,
     FLOAT = 331,
     MODULATE = 332,
     LAMBDA = 333,
     CASH = 334,
     HASH = 335,
     WIRE = 336,
     CUT = 337,
     ENDDEF = 338,
     VIRG = 339,
     LPAR = 340,
     RPAR = 341,
     LBRAQ = 342,
     RBRAQ = 343,
     LCROC = 344,
     RCROC = 345,
     WHERE = 346,
     DEF = 347,
     LAPPLY = 348,
     IMPORT = 349,
     COMPONENT = 350,
     LIBRARY = 351,
     ENVIRONMENT = 352,
     WAVEFORM = 353,
     ROUTE = 354,
     ENABLE = 355,
     CONTROL = 356,
     IPAR = 357,
     ISEQ = 358,
     ISUM = 359,
     IPROD = 360,
     INPUTS = 361,
     OUTPUTS = 362,
     STRING = 363,
     FSTRING = 364,
     IDENT = 365,
     EXTRA = 366,
     DECLARE = 367,
     CASE = 368,
     ARROW = 369,
     ASSERTBOUNDS = 370,
     LOWEST = 371,
     HIGHEST = 372,
     FLOATMODE = 373,
     DOUBLEMODE = 374,
     QUADMODE = 375,
     FIXEDPOINTMODE = 376,
     BDOC = 377,
     EDOC = 378,
     BEQN = 379,
     EEQN = 380,
     BDGM = 381,
     EDGM = 382,
     BLST = 383,
     ELST = 384,
     BMETADATA = 385,
     EMETADATA = 386,
     DOCCHAR = 387,
     NOTICE = 388,
     LISTING = 389,
     LSTTRUE = 390,
     LSTFALSE = 391,
     LSTDEPENDENCIES = 392,
     LSTMDOCTAGS = 393,
     LSTDISTRIBUTED = 394,
     LSTEQ = 395,
     LSTQ = 396
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
#define ROUND 325
#define RDTBL 326
#define RWTBL 327
#define SELECT2 328
#define SELECT3 329
#define INT 330
#define FLOAT 331
#define MODULATE 332
#define LAMBDA 333
#define CASH 334
#define HASH 335
#define WIRE 336
#define CUT 337
#define ENDDEF 338
#define VIRG 339
#define LPAR 340
#define RPAR 341
#define LBRAQ 342
#define RBRAQ 343
#define LCROC 344
#define RCROC 345
#define WHERE 346
#define DEF 347
#define LAPPLY 348
#define IMPORT 349
#define COMPONENT 350
#define LIBRARY 351
#define ENVIRONMENT 352
#define WAVEFORM 353
#define ROUTE 354
#define ENABLE 355
#define CONTROL 356
#define IPAR 357
#define ISEQ 358
#define ISUM 359
#define IPROD 360
#define INPUTS 361
#define OUTPUTS 362
#define STRING 363
#define FSTRING 364
#define IDENT 365
#define EXTRA 366
#define DECLARE 367
#define CASE 368
#define ARROW 369
#define ASSERTBOUNDS 370
#define LOWEST 371
#define HIGHEST 372
#define FLOATMODE 373
#define DOUBLEMODE 374
#define QUADMODE 375
#define FIXEDPOINTMODE 376
#define BDOC 377
#define EDOC 378
#define BEQN 379
#define EEQN 380
#define BDGM 381
#define EDGM 382
#define BLST 383
#define ELST 384
#define BMETADATA 385
#define EMETADATA 386
#define DOCCHAR 387
#define NOTICE 388
#define LISTING 389
#define LSTTRUE 390
#define LSTFALSE 391
#define LSTDEPENDENCIES 392
#define LSTMDOCTAGS 393
#define LSTDISTRIBUTED 394
#define LSTEQ 395
#define LSTQ 396




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 96 "faustparser.y"
{
    CTree*     exp;
    char* str;
    std::string* cppstr;
    bool b;
    int numvariant;
}
/* Line 1529 of yacc.c.  */
#line 339 "faustparser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE FAUSTlval;

