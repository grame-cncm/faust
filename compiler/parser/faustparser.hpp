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
     WIRE = 334,
     CUT = 335,
     ENDDEF = 336,
     VIRG = 337,
     LPAR = 338,
     RPAR = 339,
     LBRAQ = 340,
     RBRAQ = 341,
     LCROC = 342,
     RCROC = 343,
     WHERE = 344,
     DEF = 345,
     LAPPLY = 346,
     IMPORT = 347,
     COMPONENT = 348,
     LIBRARY = 349,
     ENVIRONMENT = 350,
     WAVEFORM = 351,
     ROUTE = 352,
     ENABLE = 353,
     CONTROL = 354,
     IPAR = 355,
     ISEQ = 356,
     ISUM = 357,
     IPROD = 358,
     INPUTS = 359,
     OUTPUTS = 360,
     ONDEMAND = 361,
     UPSAMPLING = 362,
     DOWNSAMPLING = 363,
     STRING = 364,
     FSTRING = 365,
     IDENT = 366,
     EXTRA = 367,
     DECLARE = 368,
     CASE = 369,
     ARROW = 370,
     ASSERTBOUNDS = 371,
     LOWEST = 372,
     HIGHEST = 373,
     FLOATMODE = 374,
     DOUBLEMODE = 375,
     QUADMODE = 376,
     FIXEDPOINTMODE = 377,
     BDOC = 378,
     EDOC = 379,
     BEQN = 380,
     EEQN = 381,
     BDGM = 382,
     EDGM = 383,
     BLST = 384,
     ELST = 385,
     BMETADATA = 386,
     EMETADATA = 387,
     DOCCHAR = 388,
     NOTICE = 389,
     LISTING = 390,
     LSTTRUE = 391,
     LSTFALSE = 392,
     LSTDEPENDENCIES = 393,
     LSTMDOCTAGS = 394,
     LSTDISTRIBUTED = 395,
     LSTEQ = 396,
     LSTQ = 397
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
#define WIRE 334
#define CUT 335
#define ENDDEF 336
#define VIRG 337
#define LPAR 338
#define RPAR 339
#define LBRAQ 340
#define RBRAQ 341
#define LCROC 342
#define RCROC 343
#define WHERE 344
#define DEF 345
#define LAPPLY 346
#define IMPORT 347
#define COMPONENT 348
#define LIBRARY 349
#define ENVIRONMENT 350
#define WAVEFORM 351
#define ROUTE 352
#define ENABLE 353
#define CONTROL 354
#define IPAR 355
#define ISEQ 356
#define ISUM 357
#define IPROD 358
#define INPUTS 359
#define OUTPUTS 360
#define ONDEMAND 361
#define UPSAMPLING 362
#define DOWNSAMPLING 363
#define STRING 364
#define FSTRING 365
#define IDENT 366
#define EXTRA 367
#define DECLARE 368
#define CASE 369
#define ARROW 370
#define ASSERTBOUNDS 371
#define LOWEST 372
#define HIGHEST 373
#define FLOATMODE 374
#define DOUBLEMODE 375
#define QUADMODE 376
#define FIXEDPOINTMODE 377
#define BDOC 378
#define EDOC 379
#define BEQN 380
#define EEQN 381
#define BDGM 382
#define EDGM 383
#define BLST 384
#define ELST 385
#define BMETADATA 386
#define EMETADATA 387
#define DOCCHAR 388
#define NOTICE 389
#define LISTING 390
#define LSTTRUE 391
#define LSTFALSE 392
#define LSTDEPENDENCIES 393
#define LSTMDOCTAGS 394
#define LSTDISTRIBUTED 395
#define LSTEQ 396
#define LSTQ 397




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 103 "faustparser.y"
{
    Tree exp;
    char* str;
    std::string* cppstr;
    bool b;
    int numvariant;
}
/* Line 1529 of yacc.c.  */
#line 341 "faustparser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE FAUSTlval;

