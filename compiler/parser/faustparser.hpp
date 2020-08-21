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
     APPL = 285,
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
     DOWNSAMPLING = 322,
     UPSAMPLING = 323,
     CLOCKSYNC = 324,
     FLOOR = 325,
     CEIL = 326,
     RINT = 327,
     RDTBL = 328,
     RWTBL = 329,
     SELECT2 = 330,
     SELECT3 = 331,
     INT = 332,
     FLOAT = 333,
     LAMBDA = 334,
     WIRE = 335,
     CUT = 336,
     ENDDEF = 337,
     VIRG = 338,
     LPAR = 339,
     RPAR = 340,
     LBRAQ = 341,
     RBRAQ = 342,
     LCROC = 343,
     RCROC = 344,
     DEF = 345,
     IMPORT = 346,
     COMPONENT = 347,
     LIBRARY = 348,
     ENVIRONMENT = 349,
     WAVEFORM = 350,
     ROUTE = 351,
     ENABLE = 352,
     CONTROL = 353,
     IPAR = 354,
     ISEQ = 355,
     ISUM = 356,
     IPROD = 357,
     INPUTS = 358,
     OUTPUTS = 359,
     ONDEMAND = 360,
     STRING = 361,
     FSTRING = 362,
     IDENT = 363,
     EXTRA = 364,
     DECLARE = 365,
     CASE = 366,
     ARROW = 367,
     FLOATMODE = 368,
     DOUBLEMODE = 369,
     QUADMODE = 370,
     BDOC = 371,
     EDOC = 372,
     BEQN = 373,
     EEQN = 374,
     BDGM = 375,
     EDGM = 376,
     BLST = 377,
     ELST = 378,
     BMETADATA = 379,
     EMETADATA = 380,
     DOCCHAR = 381,
     NOTICE = 382,
     LISTING = 383,
     LSTTRUE = 384,
     LSTFALSE = 385,
     LSTDEPENDENCIES = 386,
     LSTMDOCTAGS = 387,
     LSTDISTRIBUTED = 388,
     LSTEQ = 389,
     LSTQ = 390
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
#define APPL 285
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
#define DOWNSAMPLING 322
#define UPSAMPLING 323
#define CLOCKSYNC 324
#define FLOOR 325
#define CEIL 326
#define RINT 327
#define RDTBL 328
#define RWTBL 329
#define SELECT2 330
#define SELECT3 331
#define INT 332
#define FLOAT 333
#define LAMBDA 334
#define WIRE 335
#define CUT 336
#define ENDDEF 337
#define VIRG 338
#define LPAR 339
#define RPAR 340
#define LBRAQ 341
#define RBRAQ 342
#define LCROC 343
#define RCROC 344
#define DEF 345
#define IMPORT 346
#define COMPONENT 347
#define LIBRARY 348
#define ENVIRONMENT 349
#define WAVEFORM 350
#define ROUTE 351
#define ENABLE 352
#define CONTROL 353
#define IPAR 354
#define ISEQ 355
#define ISUM 356
#define IPROD 357
#define INPUTS 358
#define OUTPUTS 359
#define ONDEMAND 360
#define STRING 361
#define FSTRING 362
#define IDENT 363
#define EXTRA 364
#define DECLARE 365
#define CASE 366
#define ARROW 367
#define FLOATMODE 368
#define DOUBLEMODE 369
#define QUADMODE 370
#define BDOC 371
#define EDOC 372
#define BEQN 373
#define EEQN 374
#define BDGM 375
#define EDGM 376
#define BLST 377
#define ELST 378
#define BMETADATA 379
#define EMETADATA 380
#define DOCCHAR 381
#define NOTICE 382
#define LISTING 383
#define LSTTRUE 384
#define LSTFALSE 385
#define LSTDEPENDENCIES 386
#define LSTMDOCTAGS 387
#define LSTDISTRIBUTED 388
#define LSTEQ 389
#define LSTQ 390




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 81 "faustparser.y"
{
	CTree* 	exp;
	char* str;
	string* cppstr;
	bool b;
	int numvariant;
}
/* Line 1529 of yacc.c.  */
#line 327 "faustparser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

