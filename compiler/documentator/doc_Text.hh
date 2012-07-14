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

#ifndef _doc_stringFAUST_H
#define _doc_stringFAUST_H

/**********************************************************************
			- string.h : Chaines de caractere -


		Historique :
		-----------
		17-11-2001 : implementation initiale (yo)
		2009-08-17 : adaptation pour documentator (kb)
***********************************************************************/
#include <string>
#include <vector>
using namespace std;

//string subst (const string& m, const string& a0);
//string subst (const string& m, const vector<string>& vargs);
//string subst (const string& m, const string& a0, const string& a1);
//string subst (const string& m, const string& a0, const string& a1, const string& a2);
//string subst (const string& model, const string& a0, const string& a1, const string& a2, const string& a3);
//string subst (const string& model, const string& a0, const string& a1, const string& a2, const string& a3, const string& a4);
//string subst (const string& model, const string& a0, const string& a1, const string& a2, const string& a3, const string& a4, const string& a5);
//string subst (const string& model, const string& a0, const string& a1, const string& a2, const string& a3, const string& a4, const string& a5, const string& a6);

string docT (char* c);
string docT (int n);
string docT (long n);
//string docT (float n);
string docT (double n);

// add and remove quotes of a string
//string unquote(const string& s);
//string quote(const string& s);


#endif
