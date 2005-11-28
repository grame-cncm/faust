
/* Parser for the Faust language */

%{

#include "tree.hh"
#include "xtended.hh"
#include "boxes.hh"
#include "prim2.hh"
#include "signals.hh"
#include "errormsg.hh"

#include <string>
#include <list>

#define YYDEBUG 1
#define YYERROR_VERBOSE 1
#define YYMAXDEPTH	100000

extern char* 		yytext;
extern const char* 	yyfilename;
extern int 			yylineno;
extern int 			yyerr;
extern Tree 		gResult;

extern list<string>	gNameProperty;
extern list<string>	gAuthorProperty;
extern list<string>	gCopyrightProperty;
extern list<string>	gVersionProperty;
extern list<string>	gLicenseProperty;

int yylex();

Tree unquote(char* str)
{
	//-----------copy unquoted filename-------------
	char buf[512]; 
	int j=0;
	 
	if (str[0] == '"') {
		//it is a quoted string, we remove the quotes
		for (int i=1; j<511 && str[i];) {
			buf[j++] = str[i++];
		}
		// remove last quote
		if (j>0) buf[j-1] = 0;
	} else {
		for (int i=0; j<511 && str[i];) {
			buf[j++] = str[i++];
		}
	}
	buf[j] = 0;
	
	return tree(buf);
	//----------------------------------------------
}

%}


%union {
	CTree* 	exp;
}

%start program
		
/* With local environment (lowest priority)*/
%left WITH

/* Block Diagram Algebra */
/*%left SEQ SPLIT MIX*/
%left SPLIT MIX
%left SEQ
%left PAR
%left REC

/* Primitive boxes */	
			
%left LT LE EQ GT GE NE

%left ADD SUB OR
%left MUL DIV MOD AND XOR LSH RSH
%left FDELAY
%left DELAY1
%left APPL DOT


%token MEM
%token PREFIX

%token INTCAST
%token FLOATCAST
%token FFUNCTION
%token FCONSTANT

%token BUTTON
%token CHECKBOX
%token VSLIDER
%token HSLIDER
%token NENTRY
%token VGROUP
%token HGROUP
%token TGROUP

%token HBARGRAPH
%token VBARGRAPH
%token ATTACH


%token ACOS
%token ASIN
%token ATAN
%token ATAN2
%token COS
%token SIN
%token TAN

%token EXP
%token LOG
%token LOG10
%token POW
%token SQRT

%token ABS
%token MIN
%token MAX

%token FMOD
%token REMAINDER

%token FLOOR
%token CEIL
%token RINT


	   
%token RDTBL
%token RWTBL
	   
%token SELECT2
%token SELECT3
		
%token INT
%token FLOAT


%token LAMBDA
%token DOT

%token WIRE
%token CUT
%token ENDDEF
%token VIRG
%token LPAR
%token RPAR
%token LBRAQ
%token RBRAQ
%token WITH
%token DEF

%token IMPORT
%token COMPONENT

%token IPAR
%token ISEQ
%token ISUM
%token IPROD

%token STRING   
%token FSTRING   
%token IDENT
%token EXTRA   

%token DECLARE 

%token NAMEPROP
%token AUTHORPROP
%token COPYRIGHTPROP
%token VERSIONPROP 
%token LICENSEPROP	


%type <exp> program

%type <exp> eqlist
%type <exp> equation

%type <exp> params

%type <exp> diagram
%type <exp> eqname
%type <exp> expression
%type <exp> primitive
%type <exp> argument
%type <exp> arglist

%type <exp> ident
%type <exp> name

%type <exp> ffunction
%type <exp> fconst
%type <exp> signature
%type <exp> string
%type <exp> uqstring
%type <exp> fstring
%type <exp> type
%type <exp> typelist
%type <exp> fun

%type <exp> fpar
%type <exp> fseq
%type <exp> fsum
%type <exp> fprod

%type <exp> button	
%type <exp> checkbox
%type <exp> vslider	
%type <exp> hslider	
%type <exp> nentry	
%type <exp> vgroup	
%type <exp> hgroup	
%type <exp> tgroup	

%type <exp> vbargraph	
%type <exp> hbargraph	
	


		
		
		
		


%% /* grammar rules and actions follow */

program         : eqlist 						{$$ = $1; gResult = $$; }
				;

eqlist			: /*empty*/						{$$ = nil; }
				| eqlist equation 				{$$ = cons ($2,$1); } 
                ;
				
equation		: eqname LPAR params RPAR DEF diagram ENDDEF	{$$ = cons($1,buildBoxAbstr($3,$6)); } 
				| eqname DEF diagram ENDDEF						{$$ = cons($1,$3); } 
				| IMPORT LPAR uqstring RPAR ENDDEF				{$$ = importFile($3); }
				| DECLARE NAMEPROP 		STRING {gNameProperty.push_back(yytext); } 		ENDDEF				{$$ = nil; }
				| DECLARE AUTHORPROP 	STRING {gAuthorProperty.push_back(yytext); } 	ENDDEF				{$$ = nil; }
				| DECLARE COPYRIGHTPROP STRING {gCopyrightProperty.push_back(yytext); } ENDDEF				{$$ = nil; }
				| DECLARE VERSIONPROP 	STRING {gVersionProperty.push_back(yytext); } 	ENDDEF				{$$ = nil; }
				| DECLARE LICENSEPROP 	STRING {gLicenseProperty.push_back(yytext); } 	ENDDEF				{$$ = nil; }
				| error ENDDEF									{$$ = nil; yyerr++;}
               	;
				
eqname			: ident 						{$$=$1; setDefProp($1, yyfilename, yylineno); }
				;
				
params			: ident							{$$ = cons($1,nil); }
				| params PAR ident				{$$ = cons($3,$1); } 
                ;
					
diagram			: diagram WITH LBRAQ eqlist RBRAQ	{$$ = boxWithLocalDef($1,$4); }	
				| diagram PAR diagram  			{$$ = boxPar($1,$3);}
				| diagram SEQ diagram  			{$$ = boxSeq($1,$3);}
				| diagram SPLIT  diagram 		{$$ = boxSplit($1,$3);}
				| diagram MIX diagram 			{$$ = boxMerge($1,$3);}
				| diagram REC diagram  			{$$ = boxRec($1,$3);}
				| expression					{$$ = $1; }
				;
				
expression		: expression ADD expression 	{$$ = boxSeq(boxPar($1,$3),boxPrim2(sigAdd)); }
				| expression SUB expression 	{$$ = boxSeq(boxPar($1,$3),boxPrim2(sigSub)); }
				| expression MUL expression 	{$$ = boxSeq(boxPar($1,$3),boxPrim2(sigMul)); }
				| expression DIV expression 	{$$ = boxSeq(boxPar($1,$3),boxPrim2(sigDiv)); }
				| expression MOD expression 	{$$ = boxSeq(boxPar($1,$3),boxPrim2(sigRem)); }
				| expression FDELAY expression 	{$$ = boxSeq(boxPar($1,$3),boxPrim2(sigFixDelay)); }
				| expression DELAY1  			{$$ = boxSeq($1,boxPrim1(sigDelay1)); }
				| expression DOT ident  		{$$ = boxAccess($1,$3); }

				| expression AND expression 	{$$ = boxSeq(boxPar($1,$3),boxPrim2(sigAND)); }
				| expression OR expression 		{$$ = boxSeq(boxPar($1,$3),boxPrim2(sigOR)); }
				| expression XOR expression 	{$$ = boxSeq(boxPar($1,$3),boxPrim2(sigXOR)); }

				| expression LSH expression 	{$$ = boxSeq(boxPar($1,$3),boxPrim2(sigLeftShift)); }
				| expression RSH expression 	{$$ = boxSeq(boxPar($1,$3),boxPrim2(sigRightShift)); }
				
				| expression LT expression  	{$$ = boxSeq(boxPar($1,$3),boxPrim2(sigLT)); }
				| expression LE expression  	{$$ = boxSeq(boxPar($1,$3),boxPrim2(sigLE)); }
				| expression GT expression  	{$$ = boxSeq(boxPar($1,$3),boxPrim2(sigGT)); }
				| expression GE expression  	{$$ = boxSeq(boxPar($1,$3),boxPrim2(sigGE)); }
				| expression EQ expression  	{$$ = boxSeq(boxPar($1,$3),boxPrim2(sigEQ)); }
				| expression NE expression		{$$ = boxSeq(boxPar($1,$3),boxPrim2(sigNE)); }
								
				| expression LPAR arglist RPAR %prec APPL	{$$ = buildBoxAppl($1,$3); }
					
				| primitive						{$$ = $1;}
				;
					
primitive		: INT   						{$$ = boxInt(atoi(yytext));}
				| FLOAT 						{$$ = boxReal(atof(yytext));}
				
				| ADD INT   					{$$ = boxInt(atoi(yytext));}
				| ADD FLOAT 					{$$ = boxReal(atof(yytext));}
				
				| SUB INT   					{$$ = boxInt(0 - atoi(yytext));}
				| SUB FLOAT 					{$$ = boxReal(0.0 - atof(yytext));}
				
				| WIRE   						{$$ = boxWire();}
				| CUT   						{$$ = boxCut();}
				
				| MEM   						{$$ = boxPrim1(sigDelay1);}
				| PREFIX   						{$$ = boxPrim2(sigPrefix);}

				| INTCAST   					{$$ = boxPrim1(sigIntCast);}
				| FLOATCAST   					{$$ = boxPrim1(sigFloatCast);}

				| ADD							{$$ = boxPrim2(sigAdd);}
				| SUB 							{$$ = boxPrim2(sigSub);}
				| MUL  							{$$ = boxPrim2(sigMul);}
				| DIV							{$$ = boxPrim2(sigDiv);}
				| MOD							{$$ = boxPrim2(sigRem);}
				| FDELAY						{$$ = boxPrim2(sigFixDelay);}

				| AND							{$$ = boxPrim2(sigAND);}
				| OR 							{$$ = boxPrim2(sigOR);}
				| XOR  							{$$ = boxPrim2(sigXOR);}

				| LSH							{$$ = boxPrim2(sigLeftShift);}
				| RSH 							{$$ = boxPrim2(sigRightShift);}
				
				| LT							{$$ = boxPrim2(sigLT);}
				| LE							{$$ = boxPrim2(sigLE);}
				| GT							{$$ = boxPrim2(sigGT);}
				| GE							{$$ = boxPrim2(sigGE);}
				| EQ							{$$ = boxPrim2(sigEQ);}
				| NE							{$$ = boxPrim2(sigNE);}
				
				| ATTACH						{$$ = boxPrim2(sigAttach);}
				
				| ACOS							{$$ = gAcosPrim->box(); }
				| ASIN							{$$ = gAsinPrim->box(); }
				| ATAN							{$$ = gAtanPrim->box(); }
				| ATAN2							{$$ = gAtan2Prim->box(); }
				| COS							{$$ = gCosPrim->box(); }
				| SIN							{$$ = gSinPrim->box(); }
				| TAN							{$$ = gTanPrim->box(); }

				| EXP							{$$ = gExpPrim->box(); }
				| LOG							{$$ = gLogPrim->box(); }
				| LOG10							{$$ = gLog10Prim->box(); }
				| POW							{$$ = gPowPrim->box(); }
				| SQRT							{$$ = gSqrtPrim->box(); }

				| ABS							{$$ = gAbsPrim->box(); }
				| MIN							{$$ = gMinPrim->box(); }
				| MAX							{$$ = gMaxPrim->box(); }

				| FMOD							{$$ = gFmodPrim->box(); }
				| REMAINDER						{$$ = gRemainderPrim->box(); }

				| FLOOR							{$$ = gFloorPrim->box(); }
				| CEIL							{$$ = gCeilPrim->box(); }
				| RINT							{$$ = gRintPrim->box(); }
				
								
				| RDTBL 						{$$ = boxPrim3(sigReadOnlyTable);}
				| RWTBL							{$$ = boxPrim5(sigWriteReadTable);}
				
				| SELECT2 						{$$ = boxPrim3(sigSelect2);}
				| SELECT3						{$$ = boxPrim4(sigSelect3);}
				
				| ident 						{$$ = $1;}
				
				| LPAR diagram RPAR				{$$ = $2;}
				| LAMBDA LPAR params RPAR DOT LPAR diagram RPAR				
												{$$ = buildBoxAbstr($3,$7);}
				| ffunction						{$$ = boxFFun($1); }
				| fconst						{$$ = $1;}
				| COMPONENT LPAR uqstring RPAR	{$$ = boxComponent($3); }
				
				| button						{$$ = $1;}
				| checkbox						{$$ = $1;}
				| vslider						{$$ = $1;}
				| hslider						{$$ = $1;}
				| nentry						{$$ = $1;}
				| vgroup						{$$ = $1;}
				| hgroup						{$$ = $1;}
				| tgroup						{$$ = $1;}
				| vbargraph						{$$ = $1;}
				| hbargraph						{$$ = $1;}

				| fpar							{$$ = $1;}
				| fseq							{$$ = $1;}
				| fsum							{$$ = $1;}
				| fprod							{$$ = $1;}
				;
				
				
ident			: IDENT							{$$ = boxIdent(yytext);}
				;
				        
name			: IDENT							{$$ = tree(yytext);}
				;
				        

	
arglist			: argument						{$$ = cons($1,nil); }
				| arglist PAR argument			{$$ = cons($3,$1); } 
				;
				
argument		: argument SEQ argument  		{$$ = boxSeq($1,$3);}
				| argument SPLIT argument 		{$$ = boxSplit($1,$3);}
				| argument MIX argument 		{$$ = boxMerge($1,$3);}
				| argument REC argument  		{$$ = boxRec($1,$3);}
				| expression					{$$ = $1;}
				;
				
string			: STRING						{$$ = tree(yytext); }
				;
				
uqstring		: STRING						{$$ = unquote(yytext); }
				;

fstring			: STRING						{$$ = tree(yytext); }
				| FSTRING						{$$ = tree(yytext); }
				;

/* description of iterative expressions */

fpar			: IPAR LPAR ident PAR argument PAR diagram RPAR
												{$$ = boxIPar($3,$5,$7);}
				;

fseq			: ISEQ LPAR ident PAR argument PAR diagram RPAR
												{$$ = boxISeq($3,$5,$7);}
				;

fsum			: ISUM LPAR ident PAR argument PAR diagram RPAR
												{$$ = boxISum($3,$5,$7);}
				;

fprod			: IPROD LPAR ident PAR argument PAR diagram RPAR
												{$$ = boxIProd($3,$5,$7);}
				;
	

/* description of foreign functions */
	
ffunction		: FFUNCTION LPAR signature PAR fstring PAR string RPAR 
												{$$ = ffunction($3,$5,$7);}
				;
												
fconst			: FCONSTANT LPAR type name PAR fstring RPAR 
												{$$ = boxFConst($3,$4,$6);}
				;
												
/* Description of user interface building blocks */
button			: BUTTON LPAR string RPAR		{$$ = boxButton($3); }
				;

checkbox		: CHECKBOX LPAR string RPAR		{$$ = boxCheckbox($3); }
				;

vslider			: VSLIDER LPAR string PAR argument PAR argument PAR argument PAR argument RPAR		
												{$$ = boxVSlider($3,$5,$7,$9,$11); }
				;
hslider			: HSLIDER LPAR string PAR argument PAR argument PAR argument PAR argument RPAR		
												{$$ = boxHSlider($3,$5,$7,$9,$11); }
				;
nentry			: NENTRY LPAR string PAR argument PAR argument PAR argument PAR argument RPAR		
												{$$ = boxNumEntry($3,$5,$7,$9,$11); }
				;
vgroup			: VGROUP LPAR string PAR diagram RPAR
												{$$ = boxVGroup($3, $5); }
				;
hgroup			: HGROUP LPAR string PAR diagram RPAR
												{$$ = boxHGroup($3, $5); }
				;
tgroup			: TGROUP LPAR string PAR diagram RPAR
												{$$ = boxTGroup($3, $5); }
				;

vbargraph		: VBARGRAPH LPAR string PAR argument PAR argument RPAR		
												{$$ = boxVBargraph($3,$5,$7); }
				;
hbargraph		: HBARGRAPH LPAR string PAR argument PAR argument RPAR		
												{$$ = boxHBargraph($3,$5,$7); }
				;


signature		: type fun LPAR typelist RPAR	{$$ = cons($1, cons($2, $4)); }
				| type fun LPAR RPAR			{$$ = cons($1, cons($2, nil)); }
				;

fun				: IDENT							{$$ = tree(yytext);}
				;
				        
typelist		: type							{$$ = cons($1,nil); }
				| typelist PAR type				{$$ = cons($3,$1); } 
                ;
				
type			: INTCAST						{$$ = tree(0); }
				| FLOATCAST						{$$ = tree(1); }
				;

%%         

