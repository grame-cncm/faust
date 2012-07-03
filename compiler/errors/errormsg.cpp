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
#include "ppbox.hh"
#include "global.hh"
#include "exception.hh"

#include <iostream>
using namespace std;

const char* yyfilename = "????";
Tree 		DEFLINEPROP = tree(symbol("DefLineProp"));

void yyerror(const char* msg)
{
    stringstream error;
    error << yyfilename << ":" << yylineno << ":" << msg << endl;
    gGlobal->gErrorCount++;
    throw faustexception(error.str());
}

void evalerror(const char* filename, int linenum, const char* msg, Tree exp)
{
    stringstream error;
    error << filename << ":" << linenum << ": ERROR: " << msg << endl;
    gGlobal->gErrorCount++;
    throw faustexception(error.str());
}

void evalerrorbox(const char* filename, int linenum, const char* msg, Tree exp)
{
    stringstream error;
    error << filename << ':' << linenum << ": ERROR: " << msg << " : " << boxpp(exp) << endl;
    gGlobal->gErrorCount++;
    throw faustexception(error.str());
}

void evalwarning(const char* filename, int linenum, const char* msg, Tree exp)
{
    stringstream error;
    error << filename << ':' << linenum << ": WARNING: " << msg << boxpp(exp) << endl;
    strncpy(gGlobal->gErrorMsg, error.str().c_str(), 256);
}

void evalremark(const char* filename, int linenum, const char* msg, Tree exp)
{
    stringstream error;
    error << filename << ':' << linenum << ": REMARK: " << msg << boxpp(exp) << endl;
    strncpy(gGlobal->gErrorMsg, error.str().c_str(), 256);
}

void setDefProp(Tree sym, const char* filename, int lineno)
{
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
