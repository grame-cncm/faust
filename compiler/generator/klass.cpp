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

extern bool gVectorSwitch;
extern bool gOpenMPSwitch;
extern int  gVecSize;

void tab (int n, ostream& fout)
{

	fout << '\n';
	while (n--)	fout << '\t';
}



/**
 * Store the loop used to compute a signal
 */
void Klass::setLoopProperty(Tree sig, Loop* l)
{
    fLoopProperty.set(sig,l);
}


/**
 * Returns the loop used to compute a signal
 */
bool Klass::getLoopProperty(Tree sig, Loop*& l)
{
    return  fLoopProperty.get(sig, l);
}



/**
 * Open a non-recursive loop on top of the stack of open loops.
 * @param size the number of iterations of the loop
 */
void Klass::openLoop(const string& size)
{
    fTopLoop = new Loop(fTopLoop, size);
}


/**
 * Open a recursive loop on top of the stack of open loops.
 * @param recsymbol the recursive symbol defined in this loop
 * @param size the number of iterations of the loop
 */
void Klass::openLoop(Tree recsymbol, const string& size)
{
    fTopLoop = new Loop(recsymbol, fTopLoop, size);  
    //cerr << "open loop :" << fTopLoop << endl;  
}


/**
 * Close the top loop and either keep it
 * or absorb it within its enclosing loop. 
 */
void Klass::closeLoop(Tree sig)
{
    assert(fTopLoop);
    Loop* l = fTopLoop;
    fTopLoop = l->fEnclosingLoop;
    assert(fTopLoop);
    //cerr << "close loop :" << l << endl;  

    if (l->isEmpty() || l->hasRecDependencies()) {
        // empty or dependent loop -> absorbed by enclosing one
        fTopLoop->absorb(l);
        delete l;
    } else {
        // we have an independent loop
        if (sig) setLoopProperty(sig,l);     // associate the signal
        fTopLoop->fLoopDependencies.insert(l);
    }
}


/**
 * Print a list of lines. 
 */
void printlines (int n, list<string>& lines, ostream& fout)
{
	list<string>::iterator s;
	for (s = lines.begin(); s != lines.end(); s++) {
		tab(n, fout); fout << *s;
	}
}



/**
 * Print the required C++ libraries as comments in source code 
 */
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





/**
 * Print the required include files 
 */
void Klass::printIncludeFile(ostream& fout)
{
	set<string> S;
	set<string>::iterator f;

    if (gOpenMPSwitch) {
        fout << "#include <omp.h>" << "\n";
    }
	collectIncludeFile(S);
	for (f = S.begin(); f != S.end(); f++) 	{
		fout << "#include " << *f << "\n";
	}
}


/**
 * Print the loop graph as a serie of 
 * parallel loops 
 */
void Klass::printLoopGraph(int n, ostream& fout)
{
    lgraph G;
    sortGraph(fTopLoop, G);
    if (!gOpenMPSwitch) {
        // normal mode (non openMP)
        for (int l=G.size()-1; l>=0; l--) {
            if (gVectorSwitch) { tab(n, fout); fout << "// PARALLEL SECTION : " << G.size() - l; }
            for (lset::const_iterator p =G[l].begin(); p!=G[l].end(); p++) {
                (*p)->println(n, fout);
            }
        }
    } else {
        // openMP mode : add openMP directives
        for (int l=G.size()-1; l>=0; l--) {
            tab(n, fout); fout << "// PARALLEL SECTION : " << G.size() - l; 
            if (G[l].size() > 1) {
                tab(n, fout); fout << "#pragma omp sections ";
                tab(n, fout); fout << "{ ";
                for (lset::const_iterator p =G[l].begin(); p!=G[l].end(); p++) {
                    tab(n+1, fout); fout << "#pragma omp section ";
                    (*p)->println(n+1, fout);
                }
                tab(n, fout); fout << "} ";
            } else if (G[l].size() == 1 && !(*G[l].begin())->isEmpty()) {
                tab(n, fout); fout << "#pragma omp single ";
                tab(n, fout); fout << "{ ";
					for (lset::const_iterator p =G[l].begin(); p!=G[l].end(); p++) {
						(*p)->println(n+1, fout);
					}
                tab(n, fout); fout << "} ";
            }    
        }
    }
}


/**
 * Print a full C++ class corresponding to a Faust dsp
 */
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

        if (!gVectorSwitch) {
            
            tab(n+1,fout); fout << "virtual void compute (int count, float** input, float** output) {";
                printlines (n+2, fSlowDecl, fout);
                printlines (n+2, fSlowCode, fout);
                printLoopGraph (n+2,fout);
                printlines (n+2, fEndCode, fout);
            tab(n+1,fout); fout << "}";

        } else {

            if (!gOpenMPSwitch) {
                // in vector mode we need to split loops in smaller pieces not larger
                // than gVecSize
                tab(n+1,fout); fout << "virtual void compute (int fullcount, float** input, float** output) {";
                    tab(n+2,fout); fout << "for (int index = 0; index < fullcount; index += " << gVecSize << ") {";
                        tab(n+3,fout); fout << "int count = min ("<< gVecSize << ", fullcount-index);";
                        printlines (n+3, fSlowDecl, fout);
                        printlines (n+3, fSlowCode, fout);
                        printLoopGraph (n+3,fout);
                        printlines (n+3, fEndCode, fout);
                    tab(n+2,fout); fout << "}";
                tab(n+1,fout); fout << "}";
            } else {
                // in openMP mode we need to split loops in smaller pieces not larger
                // than gVecSize and add openMP pragmas
                tab(n+1,fout); fout << "virtual void compute (int fullcount, float** input, float** output) {";
                    tab(n+2,fout); fout << "for (int index = 0; index < fullcount; index += " << gVecSize << ") {";
                        tab(n+3,fout); fout << "int count = min ("<< gVecSize << ", fullcount-index);";
                        printlines (n+3, fSlowDecl, fout);

                        tab(n+3,fout); fout << "#pragma omp single";
                        tab(n+3,fout); fout << "{";
                        	printlines (n+4, fSlowCode, fout);
                        tab(n+3,fout); fout << "}";

                        printLoopGraph (n+3,fout);

                        tab(n+3,fout); fout << "#pragma omp single";
                        tab(n+3,fout); fout << "{";
                        	printlines (n+4, fEndCode, fout);
                        tab(n+3,fout); fout << "}";

                    tab(n+2,fout); fout << "}";
                tab(n+1,fout); fout << "}";
            }
        }

	tab(n,fout); fout << "};\n" << endl;

	printlines (n, fStaticFields, fout);
	fout << endl;

}


/**
 * Print an auxillary C++ class corresponding to an integer init signal
 */
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
			printlines (n+2, fSlowDecl, fout);
			printlines (n+2, fSlowCode, fout);
            printLoopGraph (n+2,fout);
		tab(n+1,fout); fout << "}";

	tab(n,fout); fout << "};\n" << endl;
}


/**
 * Print an auxillary C++ class corresponding to an float init signal
 */
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
			printlines (n+2, fSlowDecl, fout);
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

string Klass::addLocalDecl (const string& ctype, const string& vname)	
{ 
	fSlowDecl.push_back(subst("static $0 \t$1;", ctype, vname));
	return vname;
}

string Klass::addLocalVecDecl (const string& ctype, const string& vname, int size)	
{ 
	fSlowDecl.push_back(subst("static $0 \t$1[$2];", ctype, vname, T(size)));
	return vname;
}

string Klass::addLocalVecDecl (const string& ctype, const string& vname, const string& size)    
{ 
    fSlowDecl.push_back(subst("static $0 \t$1[$2];", ctype, vname, size));
    return vname;
}

string Klass::addLocalCommonDecl (const string& ctype, const string& vname, const string& init)
{ 
    fSlowDecl.push_back(subst("$0 \t$1 = $2;", ctype, vname, init));
    return vname;
}

string Klass::addLocalDecl (const string& ctype, const string& vname, const string& exp)	
{ 
	//fSlowCode.push_back(subst("$0 \t$1 = $2;", ctype, vname, exp));
	fSlowDecl.push_back(subst("static $0 \t$1;", ctype, vname));
	fSlowCode.push_back(subst("$0 = $1;", vname, exp));
	return vname;
}

void Klass::addSlowExecCode (const string& str)	
{ 
	fSlowCode.push_back(str); 
}
