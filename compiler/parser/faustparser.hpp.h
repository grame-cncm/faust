/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/
 
 
 
#ifndef BISON_PARSER_FAUSTPARSER_HPP_H
# define BISON_PARSER_FAUSTPARSER_HPP_H

#ifndef YYSTYPE
typedef union {
	CTree* 	exp;
} yystype;
# define YYSTYPE yystype
#endif
# define	SEQ	257
# define	SPLIT	258
# define	MIX	259
# define	PAR	260
# define	REC	261
# define	LT	262
# define	LE	263
# define	EQ	264
# define	GT	265
# define	GE	266
# define	NE	267
# define	ADD	268
# define	SUB	269
# define	OR	270
# define	MUL	271
# define	DIV	272
# define	MOD	273
# define	AND	274
# define	XOR	275
# define	LSH	276
# define	RSH	277
# define	APPL	278
# define	MEM	279
# define	INTCAST	280
# define	FLOATCAST	281
# define	FFUNCTION	282
# define	RDTBL	283
# define	RWTBL	284
# define	INT	285
# define	FLOAT	286
# define	WIRE	287
# define	CUT	288
# define	ENDDEF	289
# define	VIRG	290
# define	LPAR	291
# define	RPAR	292
# define	DEF	293
# define	STRING	294
# define	IDENT	295
# define	EXTRA	296


extern YYSTYPE yylval;

#endif /* not BISON_PARSER_FAUSTPARSER_HPP_H */
