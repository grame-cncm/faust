#include <set>
#include "loop.hh"
extern bool gVectorSwitch;

using namespace std;

/**
 * Print n tabs (for indentation purpose)
 * @param n number of tabs to print
 * @param fout output stream
 */
static void tab (int n, ostream& fout)
{

    fout << '\n';
    while (n--) fout << '\t';
}


/**
 * Print a list of lines
 * @param n number of tabs of indentation
 * @param lines list of lines to be printed
 * @param fout output stream
 */
static void printlines (int n, list<string>& lines, ostream& fout)
{
    list<string>::iterator s;
    for (s = lines.begin(); s != lines.end(); s++) {
        tab(n, fout); fout << *s;
    }
}


/**
 * Create a recursive loop
 * @param recsymbol the recursive symbol defined in this loop
 * @param encl the enclosing loop
 * @param size the number of iterations of the loop
 */
Loop::Loop( Tree recsymbol, Loop* encl, const string& size) 
        : fIsRecursive(true), fRecSymbol(recsymbol), fEnclosingLoop(encl), fSize(size), fOrder(-1) 
{}


/**
 * Create a non recursive loop
 * @param encl the enclosing loop
 * @param size the number of iterations of the loop
 */
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
 * Test if a loop is empty that is if it contains no lines of code). 
 * @return true if the loop is empty
 */
bool Loop::isEmpty()                  
{ 
    return fExecCode.empty() && fPostCode.empty(); 
}


/**
 * Add a recursive dependency, unless it is itself
 */
void Loop::addRecDependency(Tree t)
{
    if (t != fRecSymbol) {
        fRecDependencies.insert(t);
    }
}


/**
 * Search if t is defined in this loop
 * or the enclosing ones 
 */
bool Loop::findRecDefinition(Tree t)
{
    Loop* l = this;
    while (l && l->fRecSymbol != t) l=l->fEnclosingLoop;
    return l != 0;
}


/**
 * Add a line of exec code  (begin of the loop)
 */
void Loop::addExecCode (const string& str)    
{ 
   // cerr << this << "->addExecCode " << str << endl;
    fExecCode.push_back(str); 
}


/**
 * Add a line of post exec code (end of the loop) 
 */
void Loop::addPostCode (const string& str)    
{ 
   // cerr << this << "->addPostCode " << str << endl;
    fPostCode.push_front(str); 
}


/**
 * Absorb a loop by copying its recursive dependencies, its loop dependencies
 * and its lines of exec and post exec code. 
 * @param l the Loop to be absorbed
 */
void Loop::absorb (Loop* l)    
{ 
    // the loops must have the same number of iterations
    assert(fSize == l->fSize); 

    // update recursive dependecies by adding those from the absorbed loop
    fRecDependencies.insert(l->fRecDependencies.begin(), l->fRecDependencies.end());  
    if (fIsRecursive) fRecDependencies.erase(fRecSymbol); 

    // update loop dependecies by adding those from the absorbed loop
    fLoopDependencies.insert(l->fLoopDependencies.begin(), l->fLoopDependencies.end());  

    // add the line of code of the absorbed loop
    fExecCode.insert(fExecCode.end(), l->fExecCode.begin(), l->fExecCode.end());
    fPostCode.insert(fPostCode.begin(), l->fPostCode.begin(), l->fPostCode.end());
}


/**
 * Print a loop (unless it is empty)
 * @param n number of tabs of indentation  
 * @param fout output stream  
 */
void Loop::println(int n, ostream& fout)
{
    if (fExecCode.size()+fPostCode.size() > 0) {
/*        if (gVectorSwitch) {
            tab(n,fout); 
            fout << ((fIsRecursive) ? "// recursive loop" : "// vectorizable loop");
        }*/
            
        tab(n,fout); fout << "for (int i=0; i<" << fSize << "; i++) {";
        printlines(n+1, fExecCode, fout);
        if (fPostCode.size()>0) {
            tab(n+1,fout); fout << "// post processing";
            printlines(n+1, fPostCode, fout);
        }
        tab(n,fout); fout << "}";
    }
}
