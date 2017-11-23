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
 
#include <stdio.h>

#include "signals.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"

// imprime le type d'un signal en clair
#if 0
void printSigType (Tree tp)
{
	Tree t0;
	int n, v, c;
	
	if (isTableType(tp, t0)) {
		printf("table-of "); 
		printSigType(t0);
	} else if (isSigType(tp, &n, &v, &c)) {
		putchar("NR"[n]);
		putchar("KB S"[v]);
		putchar("CI X"[c]);
		//printf(" {%d,%d,%d} ", n, v, c);
	} else {
		printf("unknown");
	}
}

void printSigTypeList (Tree l)
{
	char sep = '(';

	do {
		putchar(sep); sep = ',';
		printSigType(hd(l));
		l = tl(l);
	} while (isList(l));

	putchar(')');
}
#endif 

void printSigType (int n, int v, int c)
{
	putchar("NR"[n]);
	putchar("KB S"[v]);
	putchar("CI X"[c]);
}

const char* binopname[]= {
		"+", "-", "*", "/", "%", 
		"<<", ">>",
		">", "<", ">=", "<=", "==", "!=",
		"&", "|", "^" 
};

int binopprec[] = {
		2, 2, 3, 3, 3,
		1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 1
};		

void printSignal(Tree sig, FILE* out, int prec)
{
	int 	i;
	double	r;
    Tree 	x, y, z, u, le, id;
	    
		 if (isSigInt(sig, &i))            { fprintf(out, "%d", i); }
	else if (isSigReal(sig, &r)) 			{ fprintf(out, "%f", r); }
	else if (isSigInput(sig, &i))          { fprintf(out, "IN%d", i); }
	else if (isSigOutput(sig, &i, x))      { fprintf(out, "OUT%d := ", i); printSignal(x, out, 0); }
	
	else if (isSigBinOp(sig, &i, x, y))	{
		if (prec > binopprec[i]) fputs("(", out); 
		printSignal(x,out,binopprec[i]); fputs(binopname[i], out); printSignal(y, out, binopprec[i]); 
		if (prec > binopprec[i]) fputs(")", out); 	
	}
	else if (isSigDelay1(sig, x))           { fputs("mem(", out); printSignal(x,out,0); fputs(")", out); }
	else if (isSigPrefix(sig, x, y)) 		{ fputs("prefix(", out); printSignal(x,out,0); fputs(",", out);	 printSignal(y,out,0); fputs(")", out); }
	else if (isSigAttach(sig, x, y)) 		{ fputs("attach(", out); printSignal(x,out,0); fputs(",", out);	 printSignal(y,out,0); fputs(")", out); }
    else if (isSigEnable(sig, x, y)) 		{ fputs("enable(", out); printSignal(x,out,0); fputs(",", out);	 printSignal(y,out,0); fputs(")", out); }
    else if (isSigControl(sig, x, y))       { fputs("control(", out); printSignal(x,out,0); fputs(",", out); printSignal(y,out,0); fputs(")", out); }
    else if (isSigFixDelay(sig, x, y))      {
		if (prec > 4) fputs("(", out); 
		printSignal(x,out,4); fputs("@", out); printSignal(y, out, 4); 
		if (prec > 4) fputs(")", out); 	
	}

	else if (isProj(sig, &i, x)) 			{ printSignal(x,out,prec); fprintf(out, "#%d", i); }
    else if (isRef(sig, i)) 				{ fprintf(out, "$%d", i); }
	else if (isRef(sig, x)) 				{ print(x, out); }
	else if (isRec(sig, le))				{ fputs("\\_.", out); printSignal(le, out, prec); }
	else if (isRec(sig, x, le))             { fputs("\\", out); print(x,out); fputs(".", out); printSignal(le, out, prec); }
	
	else if (isSigTable(sig, id, x, y)) 	{ fputs("table(", out); printSignal(x,out,0); fputc(',', out); printSignal(y,out,0); fputc(')', out); }
	else if (isSigWRTbl(sig, id, x, y, z))  { printSignal(x,out,0); fputc('[',out); printSignal(y,out,0); fputs("] := (", out); printSignal(z,out,0); fputc(')', out); }
	else if (isSigRDTbl(sig, x, y)) 		{ printSignal(x,out,0); fputc('[', out); printSignal(y,out,0); fputc(']', out); }

    else if (isSigDocConstantTbl(sig,x,y)) 	{ fputs("sigDocConstantTbl(", out); printSignal(x,out,0); fputc(',', out);
                                                                                printSignal(y,out,0); fputc(')', out); }

    else if (isSigDocWriteTbl(sig,x,y,z,u)) { fputs("sigDocWriteTbl(", out);    printSignal(x,out,0); fputc(',', out);
                                                                                printSignal(y,out,0); fputc(',', out);
                                                                                printSignal(z,out,0); fputc(',', out);
                                                                                printSignal(u,out,0); fputc(')', out); }

    else if (isSigDocAccessTbl(sig,x,y)) 	{ fputs("sigDocAccessTbl(", out);   printSignal(x,out,0); fputc(',', out);
                                                                                printSignal(y,out,0); fputc(')', out); }

	else if (isSigGen(sig, x))              { printSignal(x,out,prec); }
 
	else if (isSigIntCast(sig, x))          { fputs("int(", out); printSignal(x,out,0); fputs(")", out); }
	else if (isSigFloatCast(sig, x)) 		{ fputs("float(", out); printSignal(x,out,0); fputs(")", out); }

	else if (isList(sig)) {
		char sep = '{';
		do { 
			fputc(sep, out);
			printSignal(hd(sig), out, 0);
			sep=',';
			sig = tl(sig);
		} while (isList(sig));
		fputc('}', out);
	} else {
		print(sig, out);
    }
}
