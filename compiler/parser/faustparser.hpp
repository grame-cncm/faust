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
# define	APPL	279
# define	MEM	280
# define	INTCAST	281
# define	FLOATCAST	282
# define	FFUNCTION	283
# define	FCONSTANT	284
# define	BUTTON	285
# define	CHECKBOX	286
# define	VSLIDER	287
# define	HSLIDER	288
# define	NENTRY	289
# define	VGROUP	290
# define	HGROUP	291
# define	TGROUP	292
# define	RDTBL	293
# define	RWTBL	294
# define	SELECT2	295
# define	SELECT3	296
# define	INT	297
# define	FLOAT	298
# define	WIRE	299
# define	CUT	300
# define	ENDDEF	301
# define	VIRG	302
# define	LPAR	303
# define	RPAR	304
# define	LBRAQ	305
# define	RBRAQ	306
# define	DEF	307
# define	IPAR	308
# define	ISEQ	309
# define	ISUM	310
# define	IPROD	311
# define	STRING	312
# define	FSTRING	313
# define	IDENT	314
# define	EXTRA	315


extern YYSTYPE yylval;

#endif /* not BISON_PARSER_FAUSTPARSER_HPP */
