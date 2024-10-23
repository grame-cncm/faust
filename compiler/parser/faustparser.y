/* -*- Mode: C++; tab-width: 4; c-basic-offset: 4 -*- */

/* Parser for the Faust language */

%{

#include "global.hh"
#include "tree.hh"
#include "xtended.hh"
#include "boxes.hh"
#include "prim2.hh"
#include "errormsg.hh"
#include "sourcereader.hh"
#include "doc.hh"
#include "ppbox.hh"

#include <string>
#include <list>

#define YYDEBUG 1
#define YYERROR_VERBOSE 1
#define YYMAXDEPTH    100000
    
using namespace std;

extern char*        FAUSTtext;
extern const char*  FAUSTfilename;
extern int          FAUSTlineno;
extern int          FAUSTerr;

int FAUSTlex();

void yyerror(char* msg) 
{
    std::stringstream error;
    error << FAUSTfilename << " : " << FAUSTlineno << " : ERROR : " << msg << endl;
    gGlobal->gErrorCount++;
    throw faustexception(error.str());
}


//----------------------------------------------------------
// A definition is accepted if the prefixset is empty or if
// the current float precision is member of the prefix set
//----------------------------------------------------------
inline bool acceptdefinition(int prefixset)
{
    int precisions[] = {0, 1, 2, 4, 8};
    return (prefixset==0) || (prefixset & precisions[gGlobal->gFloatSize]);
}
    
//----------------------------------------------------------
// 'atoi' does not work correctly on Windows with MSVC on values
// greater than 2^31 (= 2147483648)
//----------------------------------------------------------
inline int str2int(const char* str)
{
    int result = 0;
    while (*str != 0) {
        result = result * 10 + *str - '0';
        str++;
    }
    return result;
}

//----------------------------------------------------------
// unquote() : remove enclosing quotes and carriage return 
// characters from string. Returns a Tree 
//----------------------------------------------------------
inline char replaceCR(char c)
{
    return (c != '\n') ? c : ' ';
}

inline Tree unquote(char* str)
{
    size_t size = strlen(str) + 1;
    
    //-----------copy unquoted filename-------------
    char* buf = (char*)alloca(size);
    size_t j=0;

    if (str[0] == '"') {
        // it is a quoted string, we remove the quotes
        for (size_t i=1; j<size-1 && str[i];) {
            buf[j++] = replaceCR(str[i++]);
        }
        // remove last quote
        if (j>0) buf[j-1] = 0;
    } else {
        for (size_t i=0; j<size-1 && str[i];) {
            buf[j++] = replaceCR(str[i++]);
        }
    }
    buf[j] = 0;

    return tree(buf);
    //----------------------------------------------
}

%}

%union {
    CTreeBase*     exp;
    char* str;
    std::string* cppstr;
    bool b;
    int numvariant;
}

%start program

/* With local environment (lowest priority)*/
%left WITH
%left LETREC

/* Block Diagram Algebra */
/*%left SEQ SPLIT MIX*/
%right SPLIT MIX
%right SEQ
%right PAR
%left REC

/* Primitive boxes */

%left LT LE EQ GT GE NE

%left ADD SUB OR
%left MUL DIV MOD AND XOR LSH RSH
%left POWOP
%left FDELAY
%left DELAY1
/*%left APPL*/
%left DOT

%token MEM
%token PREFIX

%token INTCAST
%token FLOATCAST
%token NOTYPECAST
%token FFUNCTION
%token FCONSTANT
%token FVARIABLE

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
%token SOUNDFILE

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
%token POWFUN
%token SQRT

%token ABS
%token MIN
%token MAX

%token FMOD
%token REMAINDER

%token FLOOR
%token CEIL
%token RINT
%token ROUND

%token RDTBL
%token RWTBL

%token SELECT2
%token SELECT3

%token INT
%token FLOAT

%token MODULATE
%token LAMBDA
%token DOT

%token WIRE
%token CUT
%token ENDDEF
%token VIRG
%left LPAR
%token RPAR
%token LBRAQ
%token RBRAQ
%left LCROC
%token RCROC
%token WITH
%token LETREC
%token WHERE
%token DEF
%token LAPPLY

%token IMPORT
%token COMPONENT
%token LIBRARY
%token ENVIRONMENT
%token WAVEFORM
%token ROUTE
%token ENABLE
%token CONTROL

%token IPAR
%token ISEQ
%token ISUM
%token IPROD

%token INPUTS
%token OUTPUTS

%token STRING
%token FSTRING
%token IDENT
%token EXTRA

%token DECLARE

%token CASE
%token ARROW

%token ASSERTBOUNDS
%token LOWEST
%token HIGHEST

%token FLOATMODE
%token DOUBLEMODE
%token QUADMODE
%token FIXEDPOINTMODE

 /* Begin and End tags for documentations, equations and diagrams */
%token BDOC
%token EDOC
%token BEQN
%token EEQN
%token BDGM
%token EDGM
%token BLST
%token ELST
%token BMETADATA
%token EMETADATA
%token <cppstr> DOCCHAR
%token NOTICE
%token LISTING

%token LSTTRUE
%token LSTFALSE
%token LSTDEPENDENCIES
%token LSTMDOCTAGS
%token LSTDISTRIBUTED
%token LSTEQ
%token LSTQ


%type <exp> program

%type <exp> stmtlist
%type <exp> statement

%type <exp> deflist
%type <exp> reclist
%type <exp> vallist
%type <exp> definition
%type <exp> recinition

%type <exp> params
%type <exp> modentry
%type <exp> modlist

%type <exp> expression

%type <exp> defname
%type <exp> recname
%type <exp> infixexp
%type <exp> primitive
%type <exp> argument
%type <exp> number
%type <exp> arglist

%type <exp> ident
%type <exp> name

%type <exp> ffunction
%type <exp> fconst
%type <exp> fvariable
%type <exp> signature
%type <exp> string
%type <exp> uqstring
%type <exp> fstring
%type <exp> type
%type <exp> typelist
%type <exp> argtype
%type <exp> fun

%type <exp> fpar
%type <exp> fseq
%type <exp> fsum
%type <exp> fprod

%type <exp> finputs
%type <exp> foutputs

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

%type <exp> soundfile

%type <exp> rule
%type <exp> rulelist

%type <exp> doc
%type <exp> docelem
%type <cppstr> doctxt
%type <exp> doceqn
%type <exp> docdgm
%type <exp> docntc
%type <exp> doclst
%type <exp> docmtd

%type <exp> lstattrlist
%type <exp> lstattrdef
%type <b> lstattrval

%type <numvariant> variant
%type <numvariant> variantlist

%% /* grammar rules and actions follow */

program         : stmtlist                          { $$ = $1; gGlobal->gResult = formatDefinitions($$); }
                ;

stmtlist        : /*empty*/                         { $$ = gGlobal->nil; }
                | stmtlist variantlist statement    { if (acceptdefinition($2)) $$ = cons ($3,$1); else $$=$1; }
                ;

deflist         : /*empty*/                         { $$ = gGlobal->nil; }
                | deflist variantlist definition    { if (acceptdefinition($2)) $$ = cons ($3,$1); else $$=$1;}
                ;

variantlist     : /*empty*/                         { $$ = 0; }
                | variantlist variant               { $$ = $1 | $2;}
                ;

variant            : FLOATMODE                      { $$ = 1;}
                | DOUBLEMODE                        { $$ = 2;}
                | QUADMODE                          { $$ = 4;}
                | FIXEDPOINTMODE                    { $$ = 8;}
                ;

reclist         : /*empty*/                          { $$ = gGlobal->nil; }
                | reclist recinition                 { $$ = cons ($2,$1); }
                ;

// vallist      : argument                           { $$ = cons($1,nil); }
//                 | argument PAR vallist            { $$ = cons ($1,$3); }
//                 ;
// 
vallist         : number                              { gGlobal->gWaveForm.push_back($1); }
                | vallist PAR number                  { gGlobal->gWaveForm.push_back($3); }
                ;

number          : INT                           { $$ = boxInt(str2int(FAUSTtext)); }
                | FLOAT                         { $$ = boxReal(atof(FAUSTtext)); }
                | ADD INT                       { $$ = boxInt(str2int(FAUSTtext)); }
                | ADD FLOAT                     { $$ = boxReal(atof(FAUSTtext)); }
                | SUB INT                       { $$ = boxInt(-str2int(FAUSTtext)); }
                | SUB FLOAT                     { $$ = boxReal(-atof(FAUSTtext)); }                
                ;
                            
statement       : IMPORT LPAR uqstring RPAR ENDDEF           { $$ = importFile($3); }
                | DECLARE name string  ENDDEF                { declareMetadata($2,$3); $$ = gGlobal->nil; }
                | DECLARE name name string  ENDDEF           { declareDefinitionMetadata($2,$3,$4); $$ = gGlobal->nil; }
                | definition                                 { $$ = $1; }
                | BDOC doc EDOC                              { declareDoc($2); $$ = gGlobal->nil; /* cerr << "Yacc : doc : " << *$2 << endl; */ }
                ;

doc             : /* empty */                               { $$ = gGlobal->nil; }
                | doc docelem                               { $$ = cons ($2,$1); }
                ;

docelem         : doctxt                                    { $$ = docTxt($1->c_str()); delete $1; }
                | doceqn                                    { $$ = docEqn($1); }
                | docdgm                                    { $$ = docDgm($1); }
                | docntc                                    { $$ = docNtc(); }
                | doclst                                    { $$ = docLst(); }
                | docmtd                                    { $$ = docMtd($1); }
                ;

doctxt          : /* empty */                              { $$ = new string(); }
                | doctxt DOCCHAR                           { $$ = &($1->append(FAUSTtext)); }
                ;

doceqn          : BEQN expression EEQN                          { $$ = $2; }
                ;

docdgm          : BDGM expression EDGM                          { $$ = $2; }
                ;

docntc          : NOTICE                                { }
                ;

doclst          : BLST lstattrlist ELST                 { }
                ;

lstattrlist        : /* empty */                        { }
                | lstattrlist lstattrdef                { }
                ;

lstattrdef      : LSTDEPENDENCIES LSTEQ LSTQ lstattrval LSTQ    { gGlobal->gLstDependenciesSwitch = $4; }
                | LSTMDOCTAGS LSTEQ LSTQ lstattrval LSTQ        { gGlobal->gStripDocSwitch = $4; gGlobal->gStripDocSwitch==true ? gGlobal->gStripDocSwitch=false : gGlobal->gStripDocSwitch=true; }
                | LSTDISTRIBUTED LSTEQ LSTQ lstattrval LSTQ     { gGlobal->gLstDistributedSwitch = $4; }
                ;

lstattrval      : LSTTRUE                                { $$ = true; }
                | LSTFALSE                                { $$ = false; }
                ;

docmtd          : BMETADATA name EMETADATA                { $$ = $2; }
                ;

definition      : defname LPAR arglist RPAR DEF expression ENDDEF  { $$ = cons($1,cons($3,$6)); setDefProp($1, FAUSTfilename, FAUSTlineno); }
                | defname DEF expression ENDDEF                    { $$ = cons($1,cons(gGlobal->nil,$3));  setDefProp($1, FAUSTfilename, FAUSTlineno); }
                | error ENDDEF                                     { $$ = gGlobal->nil; FAUSTerr++; }
                ;

recinition      : recname DEF expression ENDDEF               { $$ = cons($1,cons(gGlobal->nil,$3)); setDefProp($1, FAUSTfilename, FAUSTlineno); }
                | error ENDDEF                                { $$ = gGlobal->nil; FAUSTerr++; }
                ;

defname         : ident                                 { $$=$1; }
                ;

recname         : DELAY1 ident                          { $$=$2; }
                ;

params          : ident                                   { $$ = cons($1,gGlobal->nil); }
                | params PAR ident                        { $$ = cons($3,$1); }
                ;

modentry        : uqstring                                { $$ = cons($1,gGlobal->nil); }
                | uqstring SEQ argument                   { $$ = cons($1,$3); }
                ;

modlist         : modentry                                { $$ = cons($1,gGlobal->nil); }
                | modlist PAR modentry                    { $$ = cons($3,$1); }
                ;

expression      : expression WITH LBRAQ deflist RBRAQ    { $$ = boxWithLocalDef($1,formatDefinitions($4)); }
                | expression LETREC LBRAQ reclist RBRAQ  { $$ = boxWithRecDef($1,formatDefinitions($4), gGlobal->nil); }
                | expression LETREC LBRAQ reclist WHERE deflist RBRAQ    { $$ = boxWithRecDef($1,formatDefinitions($4),formatDefinitions($6)); }
                | expression PAR expression              { $$ = boxPar($1,$3); }
                | expression SEQ expression              { $$ = boxSeq($1,$3); }
                | expression SPLIT  expression           { $$ = boxSplit($1,$3); }
                | expression MIX expression              { $$ = boxMerge($1,$3); }
                | expression REC expression              { $$ = boxRec($1,$3); }
                | infixexp                               { $$ = $1; }
                ;

infixexp        : infixexp ADD infixexp     { $$ = boxSeq(boxPar($1,$3),boxAdd()); }
                | infixexp SUB infixexp     { $$ = boxSeq(boxPar($1,$3),boxSub()); }
                | infixexp MUL infixexp     { $$ = boxSeq(boxPar($1,$3),boxMul()); }
                | infixexp DIV infixexp     { $$ = boxSeq(boxPar($1,$3),boxDiv()); }
                | infixexp MOD infixexp     { $$ = boxSeq(boxPar($1,$3),boxRem()); }
                | infixexp POWOP infixexp   { $$ = boxSeq(boxPar($1,$3),boxPow()); }
                | infixexp FDELAY infixexp  { $$ = boxSeq(boxPar($1,$3),boxDelay()); }
                | infixexp DELAY1           { $$ = boxSeq($1,boxDelay1()); }
                | infixexp DOT ident        { $$ = boxAccess($1,$3); }

                | infixexp AND infixexp     { $$ = boxSeq(boxPar($1,$3),boxAND()); }
                | infixexp OR infixexp      { $$ = boxSeq(boxPar($1,$3),boxOR()); }
                | infixexp XOR infixexp     { $$ = boxSeq(boxPar($1,$3),boxXOR()); }

                | infixexp LSH infixexp     { $$ = boxSeq(boxPar($1,$3),boxLeftShift()); }
                | infixexp RSH infixexp     { $$ = boxSeq(boxPar($1,$3),boxARightShift()); }

                | infixexp LT infixexp      { $$ = boxSeq(boxPar($1,$3),boxLT()); }
                | infixexp LE infixexp      { $$ = boxSeq(boxPar($1,$3),boxLE()); }
                | infixexp GT infixexp      { $$ = boxSeq(boxPar($1,$3),boxGT()); }
                | infixexp GE infixexp      { $$ = boxSeq(boxPar($1,$3),boxGE()); }
                | infixexp EQ infixexp      { $$ = boxSeq(boxPar($1,$3),boxEQ()); }
                | infixexp NE infixexp      { $$ = boxSeq(boxPar($1,$3),boxNE()); }

                | infixexp LPAR arglist RPAR       { $$ = buildBoxAppl($1,$3); }
                | infixexp LCROC deflist RCROC     { $$ = boxModifLocalDef($1,formatDefinitions($3)); }
                
                | primitive                        { $$ = $1; }
                ;

primitive       : INT                           { $$ = boxInt(str2int(FAUSTtext)); }
                | FLOAT                         { $$ = boxReal(atof(FAUSTtext)); }

                | ADD INT                       { $$ = boxInt (str2int(FAUSTtext)); }
                | ADD FLOAT                     { $$ = boxReal(atof(FAUSTtext)); }

                | SUB INT                       { $$ = boxInt ( -str2int(FAUSTtext) ); }
                | SUB FLOAT                     { $$ = boxReal( -atof(FAUSTtext) ); }

                | WIRE                          { $$ = boxWire(); }
                | CUT                           { $$ = boxCut(); }

                | MEM                           { $$ = boxDelay1(); }
                | PREFIX                        { $$ = boxPrefix(); }

                | INTCAST                       { $$ = boxIntCast(); }
                | FLOATCAST                     { $$ = boxFloatCast(); }

                | ADD                           { $$ = boxAdd(); }
                | SUB                           { $$ = boxSub(); }
                | MUL                           { $$ = boxMul(); }
                | DIV                           { $$ = boxDiv(); }
                | MOD                           { $$ = boxRem(); }
                | FDELAY                        { $$ = boxDelay(); }

                | AND                           { $$ = boxAND(); }
                | OR                            { $$ = boxOR(); }
                | XOR                           { $$ = boxXOR(); }

                | LSH                           { $$ = boxLeftShift(); }
                | RSH                           { $$ = boxARightShift(); }

                | LT                            { $$ = boxLT(); }
                | LE                            { $$ = boxLE(); }
                | GT                            { $$ = boxGT(); }
                | GE                            { $$ = boxGE(); }
                | EQ                            { $$ = boxEQ(); }
                | NE                            { $$ = boxNE(); }

                | ATTACH                        { $$ = boxAttach(); }
                | ENABLE                        { $$ = boxEnable(); }
                | CONTROL                       { $$ = boxControl(); }

                | ACOS                           { $$ = gGlobal->gAcosPrim->box(); }
                | ASIN                           { $$ = gGlobal->gAsinPrim->box(); }
                | ATAN                           { $$ = gGlobal->gAtanPrim->box(); }
                | ATAN2                          { $$ = gGlobal->gAtan2Prim->box(); }
                | COS                            { $$ = gGlobal->gCosPrim->box(); }
                | SIN                            { $$ = gGlobal->gSinPrim->box(); }
                | TAN                            { $$ = gGlobal->gTanPrim->box(); }

                | EXP                            { $$ = gGlobal->gExpPrim->box(); }
                | LOG                            { $$ = gGlobal->gLogPrim->box(); }
                | LOG10                          { $$ = gGlobal->gLog10Prim->box(); }
                | POWOP                          { $$ = gGlobal->gPowPrim->box(); }
                | POWFUN                         { $$ = gGlobal->gPowPrim->box(); }
                | SQRT                           { $$ = gGlobal->gSqrtPrim->box(); }

                | ABS                            { $$ = gGlobal->gAbsPrim->box(); }
                | MIN                            { $$ = gGlobal->gMinPrim->box(); }
                | MAX                            { $$ = gGlobal->gMaxPrim->box(); }

                | FMOD                           { $$ = gGlobal->gFmodPrim->box(); }
                | REMAINDER                      { $$ = gGlobal->gRemainderPrim->box(); }

                | FLOOR                          { $$ = gGlobal->gFloorPrim->box(); }
                | CEIL                           { $$ = gGlobal->gCeilPrim->box(); }
                | RINT                           { $$ = gGlobal->gRintPrim->box(); }
                | ROUND                          { $$ = gGlobal->gRoundPrim->box(); }

                | RDTBL                          { $$ = boxReadOnlyTable(); }
                | RWTBL                          { $$ = boxWriteReadTable(); }

                | SELECT2                        { $$ = boxSelect2(); }
                | SELECT3                        { $$ = boxSelect3(); }

                | ASSERTBOUNDS                   { $$ = boxAssertBound(); }
                | LOWEST                         { $$ = boxLowest(); }
                | HIGHEST                        { $$ = boxHighest(); }

                | ident                          { $$ = $1; setUseProp($1, FAUSTfilename, FAUSTlineno);}
                | SUB ident                      { $$ = boxSeq(boxPar(boxInt(0),$2),boxSub()); }

                | LPAR expression RPAR            { $$ = $2; }
                | LAMBDA LPAR params RPAR DOT LPAR expression RPAR
                                                  { $$ = buildBoxAbstr($3,$7); }

                /* | MODULATE LPAR modlist RPAR DOT LPAR expression RPAR
                                                  { $$ = buildBoxModulation($3,$7); } */

                | LCROC modlist  LAPPLY  expression RCROC
                                                  { $$ = buildBoxModulation($2,$4); }

                | CASE LBRAQ rulelist RBRAQ     { $$ = boxCase(checkRulelist($3)); }
                
                | ffunction                     { $$ = boxFFun($1); }
                | fconst                        { $$ = $1; }
                | fvariable                     { $$ = $1; }
                | COMPONENT LPAR uqstring RPAR  { $$ = boxComponent($3); }
                | LIBRARY LPAR uqstring RPAR    { $$ = boxLibrary($3); }
                | ENVIRONMENT LBRAQ stmtlist RBRAQ { $$ = boxWithLocalDef(boxEnvironment(),formatDefinitions($3)); }
                | WAVEFORM LBRAQ vallist RBRAQ     { $$ = boxWaveform(gGlobal->gWaveForm); gGlobal->gWaveForm.clear(); }
                | ROUTE LPAR argument PAR argument RPAR       { $$ = boxRoute($3, $5, boxPar(boxInt(0),boxInt(0))); } // fake route
                | ROUTE LPAR argument PAR argument PAR expression RPAR       { $$ = boxRoute($3, $5, $7); }
                | button                        { $$ = $1; }
                | checkbox                      { $$ = $1; }
                | vslider                       { $$ = $1; }
                | hslider                       { $$ = $1; }
                | nentry                        { $$ = $1; }
                | vgroup                        { $$ = $1; }
                | hgroup                        { $$ = $1; }
                | tgroup                        { $$ = $1; }
                | vbargraph                     { $$ = $1; }
                | hbargraph                     { $$ = $1; }
                | soundfile                     { $$ = $1; }

                | fpar                          { $$ = $1; }
                | fseq                          { $$ = $1; }
                | fsum                          { $$ = $1; }
                | fprod                         { $$ = $1; }
                
                | finputs                       { $$ = $1; }
                | foutputs                      { $$ = $1; }
                ;

ident           : IDENT                         { $$ = boxIdent(FAUSTtext); setUseProp($$, FAUSTfilename, FAUSTlineno);  }
                ;

name            : IDENT                         { $$ = tree(FAUSTtext); setUseProp($$, FAUSTfilename, FAUSTlineno);  }
                ;

arglist         : argument                      { $$ = cons($1,gGlobal->nil); }
                | arglist PAR argument          { $$ = cons($3,$1); }
                ;

argument        : argument SEQ argument          { $$ = boxSeq($1,$3); }
                | argument SPLIT argument        { $$ = boxSplit($1,$3); }
                | argument MIX argument          { $$ = boxMerge($1,$3); }
                | argument REC argument          { $$ = boxRec($1,$3); }
                | infixexp                       { $$ = $1; }
                ;

string          : STRING                         { $$ = tree(FAUSTtext); }
                ;

uqstring        : STRING                         { $$ = unquote(FAUSTtext); }
                ;

fstring         : STRING                         { $$ = tree(FAUSTtext); }
                | FSTRING                        { $$ = tree(FAUSTtext); }
                ;

/* description of iterative expressions */

fpar            : IPAR LPAR ident PAR argument PAR expression RPAR
                                                { $$ = boxIPar($3,$5,$7); }
                ;

fseq            : ISEQ LPAR ident PAR argument PAR expression RPAR
                                                { $$ = boxISeq($3,$5,$7); }
                ;

fsum            : ISUM LPAR ident PAR argument PAR expression RPAR
                                                { $$ = boxISum($3,$5,$7); }
                ;

fprod           : IPROD LPAR ident PAR argument PAR expression RPAR
                                                { $$ = boxIProd($3,$5,$7); }
                ;

finputs         : INPUTS LPAR expression RPAR { $$ = boxInputs($3); }
                ;

foutputs        : OUTPUTS LPAR expression RPAR { $$ = boxOutputs($3); }
                ;

/* description of foreign functions */

ffunction       : FFUNCTION LPAR signature PAR fstring PAR string RPAR
                                                { $$ = ffunction($3,$5,$7); }
                ;

fconst          : FCONSTANT LPAR type name PAR fstring RPAR
                                                { $$ = boxFConst($3,$4,$6); }
                ;

fvariable       : FVARIABLE LPAR type name PAR fstring RPAR
                                                { $$ = boxFVar($3,$4,$6); }
                ;

/* Description of user interface building blocks */
button           : BUTTON LPAR uqstring RPAR    { $$ = boxButton($3); }
                ;

checkbox        : CHECKBOX LPAR uqstring RPAR    { $$ = boxCheckbox($3); }
                ;

vslider         : VSLIDER LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR
                                                { $$ = boxVSlider($3,$5,$7,$9,$11); }
                ;
hslider         : HSLIDER LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR
                                                { $$ = boxHSlider($3,$5,$7,$9,$11); }
                ;
nentry          : NENTRY LPAR uqstring PAR argument PAR argument PAR argument PAR argument RPAR
                                                { $$ = boxNumEntry($3,$5,$7,$9,$11); }
                ;
vgroup          : VGROUP LPAR uqstring PAR expression RPAR
                                                { $$ = boxVGroup($3, $5); }
                ;
hgroup          : HGROUP LPAR uqstring PAR expression RPAR
                                                { $$ = boxHGroup($3, $5); }
                ;
tgroup          : TGROUP LPAR uqstring PAR expression RPAR
                                                { $$ = boxTGroup($3, $5); }
                ;

vbargraph       : VBARGRAPH LPAR uqstring PAR argument PAR argument RPAR
                                                { $$ = boxVBargraph($3,$5,$7); }
                ;
hbargraph       : HBARGRAPH LPAR uqstring PAR argument PAR argument RPAR
                                                { $$ = boxHBargraph($3,$5,$7); }
                ;
soundfile       : SOUNDFILE LPAR uqstring PAR argument RPAR
                                                { $$ = boxSoundfile($3,$5); }
                ;

/* Description of foreign functions */
/* float sinhf|sinh|sinhl(float) */

signature       : type fun                      LPAR typelist RPAR { $$ = cons($1,cons(cons($2,cons($2,cons($2,cons($2,gGlobal->nil)))), $4)); }
                | type fun OR fun               LPAR typelist RPAR { $$ = cons($1,cons(cons($2,cons($4,cons($4,cons($4,gGlobal->nil)))), $6)); }
                | type fun OR fun OR fun        LPAR typelist RPAR { $$ = cons($1,cons(cons($2,cons($4,cons($6,cons($6,gGlobal->nil)))), $8)); }
                | type fun OR fun OR fun OR fun LPAR typelist RPAR { $$ = cons($1,cons(cons($2,cons($4,cons($6,cons($8,gGlobal->nil)))), $10)); }

                | type fun                      LPAR          RPAR { $$ = cons($1,cons(cons($2,cons($2,cons($2,cons($2,gGlobal->nil)))), gGlobal->nil)); }
                | type fun OR fun               LPAR          RPAR { $$ = cons($1,cons(cons($2,cons($4,cons($4,cons($4,gGlobal->nil)))), gGlobal->nil)); }
                | type fun OR fun OR fun        LPAR          RPAR { $$ = cons($1,cons(cons($2,cons($4,cons($6,cons($6,gGlobal->nil)))), gGlobal->nil)); }
                | type fun OR fun OR fun OR fun LPAR          RPAR { $$ = cons($1,cons(cons($2,cons($4,cons($6,cons($8,gGlobal->nil)))), gGlobal->nil)); }
                ;
                
fun             : IDENT                         { $$ = tree(FAUSTtext); }
                ;

typelist        : argtype                       { $$ = cons($1,gGlobal->nil); }
                | typelist PAR argtype          { $$ = cons($3,$1); }
                ;

rulelist        : rule                          { $$ = cons($1,gGlobal->nil); }
                | rulelist rule                 { $$ = cons($2,$1); }
                ;

rule            : LPAR arglist RPAR ARROW expression ENDDEF
                                                { $$ = cons($2,$5); }
                ;

type            : INTCAST                       { $$ = tree(0); }
                | FLOATCAST                     { $$ = tree(1); }
                ;

argtype         : INTCAST                       { $$ = tree(0); }
                | FLOATCAST                     { $$ = tree(1); }
                | NOTYPECAST                    { $$ = tree(2); }
                ;

%%
