/* -*- Mode: C++; tab-width: 4; c-basic-offset: 4 -*- */

/* Scanner for the Faust language */

%{
#include "tree.hh"
#include "faustparser.hpp"
#if defined(WIN32)
#if !defined(__MINGW32__)
// We don't want to include compatibility.hh here, since it pulls in whole lot
// of unneeded stuff which breaks other things, so here's some stuff to make
// MSVC happy.
#include <io.h>
#define isatty _isatty
#define fileno _fileno
#define YY_NO_UNISTD_H
#endif
#else
#include "compatibility.hh"
#include "errormsg.hh"

#define YY_FATAL_ERROR lexerror
#endif
%}

DIGIT    [0-9]
ID       [a-zA-Z][_a-zA-Z0-9]*
LETTER   [a-zA-Z]
NUMBER   ({DIGIT}+"."{DIGIT}*|"."{DIGIT}+|{DIGIT}+)
WSPACE   [ \t\n]
TMACRO   \\{ID}(\[(\ *({ID}|{NUMBER}),?\ *)\])?(\{(\ *({ID}|{NUMBER}),?\ *)*\})*

%option yylineno
%option nounput
%x comment
%x doc
%x lst



%%


"/*"							BEGIN(comment);
<comment>[^*\x0a\x0d]*			/* eat anything that's not a '*' 		*/
<comment>"*"+[^*/\x0a\x0d]*		/* eat up '*'s not followed by '/'s 	*/
<comment>\x0a\x0d				/* no need to increment yylineno here 	*/
<comment>\x0a					/* no need to increment yylineno here 	*/
<comment>\x0d					/* no need to increment yylineno here 	*/
<comment>"*"+"/"				BEGIN(INITIAL);

"<mdoc>"						{ BEGIN(doc); return BDOC; }
<doc>.							return DOCCHAR; /* char by char, may be slow ?? */
<doc>\n							return DOCCHAR; /* keep newline chars */
<doc>"<notice/>"				return NOTICE;  /* autoclosing tag */
<doc>"<notice />"				return NOTICE;  /* autoclosing tag */
<doc>"<listing"					{ BEGIN(lst);		return BLST; } /* autoclosing tag */
<doc>"<equation>"				{ BEGIN(INITIAL); 	return BEQN; }
"</equation>"					{ BEGIN(doc); 		return EEQN; }
<doc>"<diagram>"				{ BEGIN(INITIAL); 	return BDGM; }
"</diagram>"					{ BEGIN(doc); 		return EDGM; }
<doc>"<metadata>"				{ BEGIN(INITIAL); 	return BMETADATA; }
"</metadata>"					{ BEGIN(doc); 		return EMETADATA; }
<doc>"</mdoc>"					{ BEGIN(INITIAL); 	return EDOC; }

<lst>"true"						return LSTTRUE;
<lst>"false"					return LSTFALSE;
<lst>"dependencies"				return LSTDEPENDENCIES;
<lst>"mdoctags"					return LSTMDOCTAGS;
<lst>"distributed"				return LSTDISTRIBUTED;
<lst>"="						return LSTEQ;
<lst>"\""						return LSTQ;
<lst>"/>"						{ BEGIN(doc); 	return ELST; }


{DIGIT}+    		return INT;

{DIGIT}+"f"                             return FLOAT;
{DIGIT}+"."{DIGIT}*                     return FLOAT;
{DIGIT}+"."{DIGIT}*"f"                  return FLOAT;
{DIGIT}+"."{DIGIT}*e[-+]?{DIGIT}+       return FLOAT;
{DIGIT}+"."{DIGIT}*e[-+]?{DIGIT}+"f"    return FLOAT;
{DIGIT}+e[-+]?{DIGIT}+                  return FLOAT;
{DIGIT}+e[-+]?{DIGIT}+"f"               return FLOAT;
"."{DIGIT}+                             return FLOAT;
"."{DIGIT}+"f"                          return FLOAT;
"."{DIGIT}+e[-+]?{DIGIT}+               return FLOAT;
"."{DIGIT}+e[-+]?{DIGIT}+"f"            return FLOAT;

":"   		return SEQ;
","   		return PAR;
"<:"   		return SPLIT;
"+>"   		return MIX;
":>"   		return MIX;
"~"   		return REC;

"+"   		return ADD;
"-"   		return SUB;
"*"   		return MUL;
"/"   		return DIV;
"%"   		return MOD;
"@"			return FDELAY;
"'"			return DELAY1;

"&"   		return AND;
"|"   		return OR;
"xor"       return XOR;

"<<"   		return LSH;
">>"   		return RSH;

"<"   		return LT;
"<="   		return LE;
">"   		return GT;
">="   		return GE;
"=="   		return EQ;
"!="   		return NE;

"_"			return WIRE;
"!"			return CUT;

";"			return ENDDEF;
"="			return DEF;
"("			return LPAR;
")"			return RPAR;
"{"			return LBRAQ;
"}"			return RBRAQ;
"["			return LCROC;
"]"			return RCROC;

"\\"		return LAMBDA;
"."			return DOT;
"with"		return WITH;
"letrec"	return LETREC;

"mem"		return MEM;
"prefix"	return PREFIX;

"int"		return INTCAST;
"float"		return FLOATCAST;

"rdtable"	return RDTBL;
"rwtable"	return RWTBL;

"select2"	return SELECT2;
"select3"	return SELECT3;

"ffunction"	return FFUNCTION;
"fconstant" return FCONSTANT;
"fvariable" return FVARIABLE;

"button"	return BUTTON;
"checkbox"	return CHECKBOX;
"vslider"	return VSLIDER;
"hslider"	return HSLIDER;
"nentry"	return NENTRY;
"vgroup"	return VGROUP;
"hgroup"	return HGROUP;
"tgroup"	return TGROUP;
"vbargraph"	return VBARGRAPH;
"hbargraph"	return HBARGRAPH;
"soundfile" return SOUNDFILE;

"attach"	return ATTACH;

"acos"		return ACOS;
"asin"		return ASIN;
"atan"		return ATAN;
"atan2"		return ATAN2;

"cos"		return COS;
"sin"		return SIN;
"tan"		return TAN;

"exp"		return EXP;
"log"		return LOG;
"log10"		return LOG10;
"^"         return POWOP;
"pow"       return POWFUN;
"sqrt"		return SQRT;

"abs"		return ABS;
"min"		return MIN;
"max"		return MAX;

"fmod"		return FMOD;
"remainder"	return REMAINDER;

"floor"		return FLOOR;
"ceil"		return CEIL;
"rint"		return RINT;

"seq"		return ISEQ;
"par"		return IPAR;
"sum"		return ISUM;
"prod"		return IPROD;

"inputs"	return INPUTS;
"outputs"	return OUTPUTS;

"import"	return IMPORT;
"component" return COMPONENT;
"library"   return LIBRARY;
"environment"   return ENVIRONMENT;

"waveform"  return WAVEFORM;
"enable"   	return ENABLE;
"control"   return CONTROL;

"declare"	return DECLARE;

"case"		return CASE;
"=>"		return ARROW;

_{ID}   	return IDENT;
{ID}   		return IDENT;

"\""[^\"]*"\""	return STRING;

"<"{LETTER}*"."{LETTER}">"	return FSTRING;
"<"{LETTER}*">"				return FSTRING;


"//"[^\x0a\x0d]*	/* eat up one-line comments */

[ \t\x0a\x0d]+		/* eat up whitespace */

<<EOF>>		yyterminate();

.           printf("extra text is : %s\n", yytext); return EXTRA;


%%
int yywrap() { return 1; }
