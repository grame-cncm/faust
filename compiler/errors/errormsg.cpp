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
 
 
 
#include "errormsg.hh"
#include "boxes.hh"
#include <iostream>
using namespace std;

const char* yyfilename = "????";
int 		gErrorCount = 0;
Tree 		DEFLINEPROP = tree(symbol("DefLineProp"));

void yyerror(char* msg) 
{ 
	fprintf(stderr, "%s:%d:%s\n", yyfilename, yylineno, msg); 
	gErrorCount++;
}

void evalerror(const char* filename, int linenum, const char* msg, Tree exp)
{
	fprintf(stderr, "%s:%d: %s ", filename, linenum, msg); 
	print(exp,stderr); fprintf(stderr, "\n");
	gErrorCount++;
}


void setDefProp(Tree sym, const char* filename, int lineno)
{
	Tree loc;
	if (getProperty(sym, DEFLINEPROP, loc)) {
		const char* name;
		isBoxIdent(sym, &name);
		cerr 	<< filename << ':' << lineno << ": "
				<< "WARNING : redefinition of symbol '" << name
				<< "' previously defined in file : "
				<< tree2str(hd(loc)) << ':' << tree2int(tl(loc))
				<< endl;
	}
	setProperty(sym, DEFLINEPROP, cons(tree(filename), tree(lineno)));
}


const char* getDefFileProp(Tree sym)
{
	Tree n;
	if (getProperty(sym, DEFLINEPROP, n)) {
		return name(hd(n)->node().getSym());
	} else {
		return "????";
	}
}

int getDefLineProp(Tree sym)
{
	Tree n;
	if (getProperty(sym, DEFLINEPROP, n)) {
		return tl(n)->node().getInt();
	} else {
		return -1;
	}
}
