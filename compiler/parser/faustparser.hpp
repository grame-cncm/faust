/* A Bison parser, made by GNU Bison 1.875d.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     MIX = 258,
     SPLIT = 259,
     SEQ = 260,
     PAR = 261,
     REC = 262,
     NE = 263,
     GE = 264,
     GT = 265,
     EQ = 266,
     LE = 267,
     LT = 268,
     OR = 269,
     SUB = 270,
     ADD = 271,
     RSH = 272,
     LSH = 273,
     XOR = 274,
     AND = 275,
     MOD = 276,
     DIV = 277,
     MUL = 278,
     FDELAY = 279,
     DELAY1 = 280,
     APPL = 281,
     MEM = 282,
     PREFIX = 283,
     INTCAST = 284,
     FLOATCAST = 285,
     FFUNCTION = 286,
     FCONSTANT = 287,
     BUTTON = 288,
     CHECKBOX = 289,
     VSLIDER = 290,
     HSLIDER = 291,
     NENTRY = 292,
     VGROUP = 293,
     HGROUP = 294,
     TGROUP = 295,
     RDTBL = 296,
     RWTBL = 297,
     SELECT2 = 298,
     SELECT3 = 299,
     INT = 300,
     FLOAT = 301,
     WIRE = 302,
     CUT = 303,
     ENDDEF = 304,
     VIRG = 305,
     LPAR = 306,
     RPAR = 307,
     LBRAQ = 308,
     RBRAQ = 309,
     WITH = 310,
     DEF = 311,
     IPAR = 312,
     ISEQ = 313,
     ISUM = 314,
     IPROD = 315,
     STRING = 316,
     FSTRING = 317,
     IDENT = 318,
     EXTRA = 319
   };
#endif
#define MIX 258
#define SPLIT 259
#define SEQ 260
#define PAR 261
#define REC 262
#define NE 263
#define GE 264
#define GT 265
#define EQ 266
#define LE 267
#define LT 268
#define OR 269
#define SUB 270
#define ADD 271
#define RSH 272
#define LSH 273
#define XOR 274
#define AND 275
#define MOD 276
#define DIV 277
#define MUL 278
#define FDELAY 279
#define DELAY1 280
#define APPL 281
#define MEM 282
#define PREFIX 283
#define INTCAST 284
#define FLOATCAST 285
#define FFUNCTION 286
#define FCONSTANT 287
#define BUTTON 288
#define CHECKBOX 289
#define VSLIDER 290
#define HSLIDER 291
#define NENTRY 292
#define VGROUP 293
#define HGROUP 294
#define TGROUP 295
#define RDTBL 296
#define RWTBL 297
#define SELECT2 298
#define SELECT3 299
#define INT 300
#define FLOAT 301
#define WIRE 302
#define CUT 303
#define ENDDEF 304
#define VIRG 305
#define LPAR 306
#define RPAR 307
#define LBRAQ 308
#define RBRAQ 309
#define WITH 310
#define DEF 311
#define IPAR 312
#define ISEQ 313
#define ISUM 314
#define IPROD 315
#define STRING 316
#define FSTRING 317
#define IDENT 318
#define EXTRA 319




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 27 "parser/faustparser.y"
typedef union YYSTYPE {
	CTree* 	exp;
} YYSTYPE;
/* Line 1285 of yacc.c.  */
#line 169 "parser/faustparser.hpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



