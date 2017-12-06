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
#include "export.hh"

#include <iostream>
using namespace std;

const char* yyfilename  = "????";

void faustassert(bool cond)
{
    if (!cond) {
    #ifndef EMCC
        stacktrace(20);
    #endif
        std::stringstream str;
        str << "ASSERT : please report the stack trace and the failing DSP file to Faust developers (";
        str << "version: " << FAUSTVERSION << ", ";
        str << "options: "; gGlobal->printCompilationOptions(str);
        str << ")\n";
        throw faustexception(str.str());
    }
}

void lexerror(const char* msg)
{
    string fullmsg = "ERROR : " + string(msg) + '\n';
    throw faustexception(fullmsg);
}

void yyerror(const char* msg)
{
    stringstream error;
    error << yyfilename << " : " << yylineno << " : ERROR : " << msg << endl;
    gGlobal->gErrorCount++;
    throw faustexception(error.str());
}

void evalerror(const char* filename, int linenum, const char* msg, Tree exp)
{
    stringstream error;
    error << filename << " : " << linenum << " : ERROR : " << msg << " : " << boxpp(exp) << endl;
    gGlobal->gErrorCount++;
    throw faustexception(error.str());
}

void evalerrorbox(const char* filename, int linenum, const char* msg, Tree exp)
{
    stringstream error;
    error << filename << " : " << linenum << " : ERROR : " << msg << boxpp(exp) << endl;
    gGlobal->gErrorCount++;
    throw faustexception(error.str());
}

void evalwarning(const char* filename, int linenum, const char* msg, Tree exp)
{
    stringstream error;
    error << filename << " : " << linenum << " : WARNING : " << msg << boxpp(exp) << endl;
    gGlobal->gErrorMsg = error.str();
}

void evalremark(const char* filename, int linenum, const char* msg, Tree exp)
{
    stringstream error;
    error << filename << " : " << linenum << " : REMARK : " << msg << boxpp(exp) << endl;
    gGlobal->gErrorMsg = error.str();
}

void setDefProp(Tree sym, const char* filename, int lineno)
{
	setProperty(sym, gGlobal->DEFLINEPROP, cons(tree(filename), tree(lineno)));
}

bool hasDefProp(Tree sym)
{
    Tree n;
    return getProperty(sym, gGlobal->DEFLINEPROP, n);
}

const char* getDefFileProp(Tree sym)
{
    Tree n;
    if (getProperty(sym, gGlobal->DEFLINEPROP, n)) {
        return name(hd(n)->node().getSym());
    } else {
        return "????";
    }
}

int getDefLineProp(Tree sym)
{
    Tree n;
    if (getProperty(sym, gGlobal->DEFLINEPROP, n)) {
        return tl(n)->node().getInt();
    } else {
        return -1;
    }
}

void setUseProp(Tree sym, const char* filename, int lineno)
{
    setProperty(sym, gGlobal->USELINEPROP, cons(tree(filename), tree(lineno)));
}

const char* getUseFileProp(Tree sym)
{
    Tree n;
    if (getProperty(sym, gGlobal->USELINEPROP, n)) {
        return name(hd(n)->node().getSym());
    } else {
        return "????";
    }
}

int getUseLineProp(Tree sym)
{
    Tree n;
    if (getProperty(sym, gGlobal->USELINEPROP, n)) {
        return tl(n)->node().getInt();
    } else {
        return -1;
    }
}
