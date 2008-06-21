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
#include <string.h>
#include "Text.hh"
#include "compatibility.hh"
#include <string>
#include <vector>


static string substitution (const string& model, const vector<string>& args)
{
	char 	c;
	int 	i=0, ilast = model.length()-1;
	string 	result;
	
	while (i < ilast) {
		c = model[i++];
		if (c != '$') {
			result += c;
		} else {
			c = model[i++];
			if (c >= '0' && c <= '9') {
				result += args[c - '0'];
			} else {
				result += c;
			}
		}
	}
	if (i == ilast) result += model[i];
	return result;
}
string subst (const string& model, const vector<string>& args)
{
	return substitution(model, args);
}

string subst (const string& model, const string& a0)
{
	vector<string> args(10);
	args[0] = a0;
	return substitution (model, args);
}			

string subst (const string& model, const string& a0, const string& a1)
{
	vector<string> args(10);
	args[0] = a0;
	args[1] = a1;
	
	return substitution (model, args);
}			

string subst (const string& model, const string& a0, const string& a1, const string& a2)
{
	vector<string> args(10);
	
	args[0] = a0;
	args[1] = a1;
	args[2] = a2;
	
	return substitution (model, args);
}			

string subst (const string& model, const string& a0, const string& a1, const string& a2, const string& a3)
{
	vector<string> args(10);
	
	args[0] = a0;
	args[1] = a1;
	args[2] = a2;
	args[3] = a3;
	
	return substitution (model, args);
}	

string subst (const string& model, const string& a0, const string& a1, const string& a2, const string& a3, const string& a4)
{
	vector<string> args(10);
	
	args[0] = a0;
	args[1] = a1;
	args[2] = a2;
	args[3] = a3;
	args[4] = a4;
	
	return substitution (model, args);
}	

string subst (const string& model, const string& a0, const string& a1, const string& a2, const string& a3, const string& a4, const string& a5)
{
	vector<string> args(10);
	
	args[0] = a0;
	args[1] = a1;
	args[2] = a2;
	args[3] = a3;
	args[4] = a4;
	args[5] = a5;
	
	return substitution (model, args);
}	

// ZDEL : supprime les zeros de fin d'une chaine de carat�res repr�sentant 
// un nombre d�cimal. Attention : n'a pas de sens sur d'autres chaines !		
static void zdel(char* c)
{
	int l = strlen(c) - 1;
	while ( l>1 && c[l-1] != '.' && c[l] == '0')  c[l--]=0;
}

string T (char* c) 	{ return string(c); }
string T (int n) 	{ char c[64]; snprintf(c, 63, "%d",n); 	return string(c); }
string T (long n) 	{ char c[64]; snprintf(c, 63, "%ld",n); return string(c); }

string T (float n)
{ 
	char c[64];
	if  (n <  0.1 && n > -0.1 && n != 0.0) {
		snprintf(c, 63, "%ef", n);
	} else {
		snprintf(c, 63, "%ff", n); 
		zdel(c); 
	}
	return string(c); 
}

string T (double n) 	
{
	char c[64];
	snprintf(c, 63, "%f", n);
	zdel(c);
	return string(c);
}
