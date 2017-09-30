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
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

void copyFirstHalf(FILE* file, FILE* dst);
void copySecondHalf(FILE* file, FILE* dst);
void copyZeroHalf(FILE* file, FILE* dst);
void copyFile(FILE* file, FILE* dst);

void streamCopyLicense(istream& src, ostream& dst, const string& exceptiontag);
void streamCopyUntil(istream& src, ostream& dst, const string& until);
void streamCopyUntilEnd(istream& src, ostream& dst);
void streamCopy(istream& src, ostream& dst);

ifstream* openArchStream (const char* filename);

FILE* fopenSearch(const char* filename, string& fullpath);

const char* stripStart(const char* filename);
bool checkURL(const char* filename);
		
const char* fileBasename(const char* name); // returns a pointer on the basename part of name

string fileDirname(const string& name);        // allocate a string containing the dirname of name

string stripEnd(const string& name, const string& ext);
