#ifndef BISON_PARSER_FAUSTPARSER_HPP
# define BISON_PARSER_FAUSTPARSER_HPP

#ifndef YYSTYPE
typedef union {
	CTree* 	exp;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
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
# define	FDELAY	278
# define	DELAY1	279
# define	APPL	280
# define	MEM	281
# define	INTCAST	282
# define	FLOATCAST	283
# define	FFUNCTION	284
# define	FCONSTANT	285
# define	BUTTON	286
# define	CHECKBOX	287
# define	VSLIDER	288
# define	HSLIDER	289
# define	NENTRY	290
# define	VGROUP	291
# define	HGROUP	292
# define	TGROUP	293
# define	RDTBL	294
# define	RWTBL	295
# define	SELECT2	296
# define	SELECT3	297
# define	INT	298
# define	FLOAT	299
# define	WIRE	300
# define	CUT	301
# define	ENDDEF	302
# define	VIRG	303
# define	LPAR	304
# define	RPAR	305
# define	LBRAQ	306
# define	RBRAQ	307
# define	DEF	308
# define	IPAR	309
# define	ISEQ	310
# define	ISUM	311
# define	IPROD	312
# define	STRING	313
# define	FSTRING	314
# define	IDENT	315
# define	EXTRA	316


extern YYSTYPE yylval;

#endif /* not BISON_PARSER_FAUSTPARSER_HPP */
