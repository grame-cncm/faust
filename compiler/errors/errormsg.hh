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

#ifndef _ERRORMSG_
#define _ERRORMSG_

#include "tlib.hh"

extern int yylineno;
extern const char* yyfilename;

// associate and retrieve file and line properties to a symbol definition
void 		setDefProp(Tree sym, const char* filename, int lineno);
bool        hasDefProp(Tree sym);

const char* getDefFileProp(Tree sym);
int 		getDefLineProp(Tree sym);

// associate and retrieve file and line properties to a symbol usage
void 		setUseProp(Tree sym, const char* filename, int lineno);
const char* getUseFileProp(Tree sym);
int 		getUseLineProp(Tree sym);

// Parsing error
void 		lexerror(const char* msg);
void 		yyerror(const char* msg);

// three levels or errors, warnings and remarks are provided during evaluation
void 		evalerror(const char* filename, int linenum, const char* msg, Tree exp);
void        evalerrorbox(const char* filename, int linenum, const char* msg, Tree exp);
void 		evalwarning(const char* filename, int linenum, const char* msg, Tree exp);
void 		evalremark(const char* filename, int linenum, const char* msg, Tree exp);

#endif
