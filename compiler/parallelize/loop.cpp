#include <set>
#include "loop.hh"

using namespace std;

static void tab (int n, ostream& fout)
{

    fout << '\n';
    while (n--) fout << '\t';
}


static void printlines (int n, list<string>& lines, ostream& fout)
{
    list<string>::iterator s;
    for (s = lines.begin(); s != lines.end(); s++) {
        tab(n, fout); fout << *s;
    }
}

Loop::Loop( Tree recsymbol, Loop* encl,const string& size) 
        : fIsRecursive(true), fRecSymbol(recsymbol), fEnclosingLoop(encl), fSize(size), fOrder(-1) 
{}

Loop::Loop(Loop* encl, const string& size) 
        : fIsRecursive(false), fRecSymbol(), fEnclosingLoop(encl), fSize(size), fOrder(-1)
{}

/**
 * A loop with recursive dependencies can't be run alone. 
 * It must be included into another loop.
 * returns true is this loop has recursive dependencies
 * and must be included in an enclosing loop
 */
bool Loop::hasRecDependencies()                  
{ 
    return !fRecDependencies.empty(); 
}

/**
 * Test if a loop is empty (no lines of code). 
 */
bool Loop::isEmpty()                  
{ 
    return fExecCode.empty() && fPostCode.empty(); 
}


/**
 * Check if a recursive symbol creates a 
 * recursive dependency
 */
void Loop::trackRecDependency(Tree t)
{
    if (findRecDependency(t)) {
        fRecDependencies.insert(t);
    }
}


/**
 * Search if t is defined in an enclosing loop and 
 * therefore creates a recursive dependency. 
 */
bool Loop::findRecDependency(Tree t)
{
    Loop* l = fEnclosingLoop;
    while (l && l->fRecSymbol != t) l=l->fEnclosingLoop;
    return l != 0;
}

void Loop::addExecCode (const string& str)    
{ 
    fExecCode.push_back(str); 
}

void Loop::addPostCode (const string& str)    
{ 
    fPostCode.push_front(str); 
}

/**
 * 
 */
void Loop::absorb (Loop* l)    
{ 
    // update dependecies by adding those from the absorbed loop
    fRecDependencies.insert(l->fRecDependencies.begin(), l->fRecDependencies.end());  
    if (fIsRecursive) fRecDependencies.erase(fRecSymbol); 

    // add the line of code of the absorbed loop
    fExecCode.insert(fExecCode.end(), l->fExecCode.begin(), l->fExecCode.end());
    fPostCode.insert(fPostCode.begin(), l->fPostCode.begin(), l->fPostCode.end());
}


void Loop::println(int n, ostream& fout)
{
    tab(n,fout); fout << "for (int i=0; i<" << fSize << "; i++) {";
    printlines(n+1, fExecCode, fout);
    if (fPostCode.size()>0) {
        tab(n+1,fout); fout << "// post processing";
        printlines(n+1, fPostCode, fout);
    }
    tab(n,fout); fout << "}";
}
