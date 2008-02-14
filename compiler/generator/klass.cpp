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



 /**********************************************************************
			- klass.cpp : class C++ à remplir (projet FAUST) -


		Historique :
		-----------
		17-10-2001 : implementation initiale (yo)
		18-10-2001 : Ajout de getFreshID (yo)
		02-11-2001 : Ajout de sous classes (yo)
		06-11-2001 : modif impression des classes (yo)

***********************************************************************/


#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <map>

#include "smartpointer.hh"
#include "klass.hh"
#include "uitree.hh"
#include "Text.hh"
#include "signals.hh"

void tab (int n, ostream& fout)
{

	fout << '\n';
	while (n--)	fout << '\t';
}



/**
 * Open a non-recursive loop on top of the loop stack
 */
void Klass::openLoop(const string& size)
{
    fTopLoop = new Loop(fTopLoop, size);
}


/**
 * Open a recursive loop on top of the loop stack
 */
void Klass::openLoop(Tree recsymbol, const string& size)
{
    fTopLoop = new Loop(recsymbol, fTopLoop, size);    
}


/**
 * Close the top loop and either store it in the loop set
 * or merge it within the enclosing one
 */
void Klass::closeLoop()
{
    assert(fTopLoop);
    Loop* l = fTopLoop;
    fTopLoop = l->fEnclosingLoop;

    if (l->isEmpty()) {
        // empty loops are just deleted
        delete l;
    } else if (l->hasRecDependencies()) {
        // not an independent loop, must be
        // absorbed by enclosing loop
        assert(fTopLoop);
        fTopLoop->absorb(l);
        delete l;
    } else {
        // it is an independent loop. It must
        // be computed before the enclosing one

        if (fTopLoop != 0) {
            fTopLoop->fLoopDependencies.insert(l);
        }
        //fLoopSet.insert(l);
    }
}

void printlines (int n, list<string>& lines, ostream& fout)
{
	list<string>::iterator s;
	for (s = lines.begin(); s != lines.end(); s++) {
		tab(n, fout); fout << *s;
	}
}


void Klass::printLibrary(ostream& fout)
{
	set<string> S;
	set<string>::iterator f;

	string sep;
	collectLibrary(S);
	fout << "/* link with ";
	for (f = S.begin(), sep =": "; f != S.end(); f++, sep = ", ") 	{
		fout << sep << *f;
	}
	fout << " */\n";
}


void Klass::printIncludeFile(ostream& fout)
{
	set<string> S;
	set<string>::iterator f;

	collectIncludeFile(S);
	for (f = S.begin(); f != S.end(); f++) 	{
		fout << "#include " << *f << "\n";
	}
}

void Klass::printLoopGraph(int n, ostream& fout)
{
    lgraph G;
    sortGraph(fTopLoop, G);
    for (int l=G.size()-1; l>=0; l--) {
        tab(n, fout); fout << "// level : " << l << endl;
        for (lset::const_iterator p =G[l].begin(); p!=G[l].end(); p++) {
            (*p)->println(n, fout);
        }
    }
}

void Klass::println(int n, ostream& fout)
{
	list<Klass* >::iterator k;

	tab(n,fout); fout << "class " << fKlassName << " : public " << fSuperKlassName << " {";

	tab(n,fout); fout << "  private:";

		for (k = fSubClassList.begin(); k != fSubClassList.end(); k++) 	(*k)->println(n+1, fout);

		printlines(n+1, fDeclCode, fout);

	tab(n,fout); fout << "  public:";

		tab(n+1,fout); fout 	<< "virtual int getNumInputs() \t{ "
						<< "return " << fNumInputs
						<< "; }";
		tab(n+1,fout); fout 	<< "virtual int getNumOutputs() \t{ "
						<< "return " << fNumOutputs
						<< "; }";

		tab(n+1,fout); fout << "static void classInit(int samplingFreq) {";
			printlines (n+2, fStaticInitCode, fout);
		tab(n+1,fout); fout << "}";

		tab(n+1,fout); fout << "virtual void instanceInit(int samplingFreq) {";
			tab(n+2,fout); fout << "fSamplingFreq = samplingFreq;";
			printlines (n+2, fInitCode, fout);
		tab(n+1,fout); fout << "}";

		tab(n+1,fout); fout << "virtual void init(int samplingFreq) {";
			tab(n+2,fout); fout << "classInit(samplingFreq);";
			tab(n+2,fout); fout << "instanceInit(samplingFreq);";
		tab(n+1,fout); fout << "}";


		tab(n+1,fout); fout << "virtual void buildUserInterface(UI* interface) {";
			printlines (n+2, fUICode, fout);
		tab(n+1,fout); fout << "}";

		tab(n+1,fout); fout << "virtual void compute (int count, float** input, float** output) {";
			printlines (n+2, fSlowCode, fout);
            printLoopGraph (n+2,fout);
		tab(n+1,fout); fout << "}";

	tab(n,fout); fout << "};\n" << endl;

	printlines (n, fStaticFields, fout);
	fout << endl;

}


void SigIntGenKlass::println(int n, ostream& fout)
{
	list<Klass* >::iterator k;

	tab(n,fout); fout << "class " << fKlassName << " {";

	tab(n,fout); fout << "  private:";
		tab(n+1,fout); fout << "int \tfSamplingFreq;";

		for (k = fSubClassList.begin(); k != fSubClassList.end(); k++) 	(*k)->println(n+1, fout);

		printlines(n+1, fDeclCode, fout);

	tab(n,fout); fout << "  public:";

		tab(n+1,fout); fout 	<< "int getNumInputs() \t{ "
						<< "return " << fNumInputs << "; }";
		tab(n+1,fout); fout 	<< "int getNumOutputs() \t{ "
						<< "return " << fNumOutputs << "; }";

		tab(n+1,fout); fout << "void init(int samplingFreq) {";
			tab(n+2,fout); fout << "fSamplingFreq = samplingFreq;";
			printlines (n+2, fInitCode, fout);
		tab(n+1,fout); fout << "}";

		tab(n+1,fout); fout << "void fill (int count, int output[]) {";
			printlines (n+2, fSlowCode, fout);
            printLoopGraph (n+2,fout);
		tab(n+1,fout); fout << "}";

	tab(n,fout); fout << "};\n" << endl;
}


void SigFloatGenKlass::println(int n, ostream& fout)
{
	list<Klass* >::iterator k;

	tab(n,fout); fout << "class " << fKlassName << " {";

	tab(n,fout); fout << "  private:";
		tab(n+1,fout); fout << "int \tfSamplingFreq;";

		for (k = fSubClassList.begin(); k != fSubClassList.end(); k++) 	(*k)->println(n+1, fout);

		printlines(n+1, fDeclCode, fout);

	tab(n,fout); fout << "  public:";

		tab(n+1,fout); fout 	<< "int getNumInputs() \t{ "
						<< "return " << fNumInputs << "; }";
		tab(n+1,fout); fout 	<< "int getNumOutputs() \t{ "
						<< "return " << fNumOutputs << "; }";

		tab(n+1,fout); fout << "void init(int samplingFreq) {";
			tab(n+2,fout); fout << "fSamplingFreq = samplingFreq;";
			printlines (n+2, fInitCode, fout);
		tab(n+1,fout); fout << "}";

		tab(n+1,fout); fout << "void fill (int count, float output[]) {";
			printlines (n+2, fSlowCode, fout);
            printLoopGraph(n+2,fout);
		tab(n+1,fout); fout << "}";

	tab(n,fout); fout << "};\n" << endl;
}

static void merge (set<string>& dst, set<string>& src)
{
	set<string>::iterator i;
	for (i = src.begin(); i != src.end(); i++)  dst.insert(*i);
}

void Klass::collectIncludeFile(set<string>& S)
{
	list<Klass* >::iterator 	k;

	for (k = fSubClassList.begin(); k != fSubClassList.end(); k++) 	(*k)->collectIncludeFile(S);
	merge(S, fIncludeFileSet);
}

void Klass::collectLibrary(set<string>& S)
{
	list<Klass* >::iterator 	k;

	for (k = fSubClassList.begin(); k != fSubClassList.end(); k++) 	(*k)->collectLibrary(S);
	merge(S, fLibrarySet);
}
