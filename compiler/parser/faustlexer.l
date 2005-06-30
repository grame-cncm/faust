/* Scanner for the Faust language */

%{
#include "tree.hh"
#include "faustparser.hpp"
%}

DIGIT    [0-9]
ID       [a-zA-Z][_a-zA-Z0-9]*
LETTER   [a-zA-Z]

%option yylineno
%x comment

%%

"/*"         			BEGIN(comment);
<comment>[^*\n]*        /* eat anything that's not a '*' 		*/
<comment>"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s 	*/
<comment>\n             /* no need to increment yylineno here 	*/
<comment>"*"+"/"        BEGIN(INITIAL);
 

{DIGIT}+    		return INT;


{DIGIT}+"."{DIGIT}* return FLOAT;
"."{DIGIT}+ 		return FLOAT;


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
"^"   		return XOR;

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

"\\"		return LAMBDA;
"."			return DOT;
"with"		return WITH;

"mem"		return MEM;
"prefix"	return PREFIX;

"int"		return INTCAST;
"float"		return FLOATCAST;

"rdtable"	return RDTBL;
"rwtable"	return RWTBL;

"select2"	return SELECT2;
"select3"	return SELECT3;

"ffunction"	return FFUNCTION; 
"fconstant"	return FCONSTANT; 

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
"attach"	return ATTACH;

"seq"		return ISEQ;
"par"		return IPAR;
"sum"		return ISUM;
"prod"		return IPROD;

"import"	return IMPORT;
"component"	return COMPONENT;

_{ID}   	return IDENT;
{ID}   		return IDENT;

"\""[^\"]*"\""	return STRING;

"<"{LETTER}*"."{LETTER}">"	return FSTRING;
"<"{LETTER}*">"				return FSTRING;


"//"[^\n]*    	/* eat up one-line comments 	*/

[ \t\n]+        /* eat up whitespace */
		
<<EOF>>		yyterminate();

.           printf("extra text is : %s\n", yytext); return EXTRA;

%%
int yywrap() { return 1; }

