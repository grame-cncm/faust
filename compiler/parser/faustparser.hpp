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
     LAMBDA = 332,
     WIRE = 333,
     CUT = 334,
     ENDDEF = 335,
     VIRG = 336,
     LPAR = 337,
     RPAR = 338,
     LBRAQ = 339,
     RBRAQ = 340,
     LCROC = 341,
     RCROC = 342,
     WHERE = 343,
     DEF = 344,
     IMPORT = 345,
     COMPONENT = 346,
     LIBRARY = 347,
     ENVIRONMENT = 348,
     WAVEFORM = 349,
     ROUTE = 350,
     ENABLE = 351,
     CONTROL = 352,
     IPAR = 353,
     ISEQ = 354,
     ISUM = 355,
     IPROD = 356,
     INPUTS = 357,
     OUTPUTS = 358,
     STRING = 359,
     FSTRING = 360,
     IDENT = 361,
     EXTRA = 362,
     DECLARE = 363,
     CASE = 364,
     ARROW = 365,
     ASSERTBOUNDS = 366,
     LOWEST = 367,
     HIGHEST = 368,
     FLOATMODE = 369,
     DOUBLEMODE = 370,
     QUADMODE = 371,
     FIXEDPOINTMODE = 372,
     BDOC = 373,
     EDOC = 374,
     BEQN = 375,
     EEQN = 376,
     BDGM = 377,
     EDGM = 378,
     BLST = 379,
     ELST = 380,
     BMETADATA = 381,
     EMETADATA = 382,
     DOCCHAR = 383,
     NOTICE = 384,
     LISTING = 385,
     LSTTRUE = 386,
     LSTFALSE = 387,
     LSTDEPENDENCIES = 388,
     LSTMDOCTAGS = 389,
     LSTDISTRIBUTED = 390,
     LSTEQ = 391,
     LSTQ = 392
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
#define LAMBDA 332
#define WIRE 333
#define CUT 334
#define ENDDEF 335
#define VIRG 336
#define LPAR 337
#define RPAR 338
#define LBRAQ 339
#define RBRAQ 340
#define LCROC 341
#define RCROC 342
#define WHERE 343
#define DEF 344
#define IMPORT 345
#define COMPONENT 346
#define LIBRARY 347
#define ENVIRONMENT 348
#define WAVEFORM 349
#define ROUTE 350
#define ENABLE 351
#define CONTROL 352
#define IPAR 353
#define ISEQ 354
#define ISUM 355
#define IPROD 356
#define INPUTS 357
#define OUTPUTS 358
#define STRING 359
#define FSTRING 360
#define IDENT 361
#define EXTRA 362
#define DECLARE 363
#define CASE 364
#define ARROW 365
#define ASSERTBOUNDS 366
#define LOWEST 367
#define HIGHEST 368
#define FLOATMODE 369
#define DOUBLEMODE 370
#define QUADMODE 371
#define FIXEDPOINTMODE 372
#define BDOC 373
#define EDOC 374
#define BEQN 375
#define EEQN 376
#define BDGM 377
#define EDGM 378
#define BLST 379
#define ELST 380
#define BMETADATA 381
#define EMETADATA 382
#define DOCCHAR 383
#define NOTICE 384
#define LISTING 385
#define LSTTRUE 386
#define LSTFALSE 387
#define LSTDEPENDENCIES 388
#define LSTMDOCTAGS 389
#define LSTDISTRIBUTED 390
#define LSTEQ 391
#define LSTQ 392




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
#line 331 "faustparser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE FAUSTlval;

