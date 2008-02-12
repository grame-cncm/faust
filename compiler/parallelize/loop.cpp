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
        : fIsRecursive(true), fRecSymbol(recsymbol), fEnclosingLoop(encl), fSize(size) 
{}

Loop::Loop(Loop* encl, const string& size) 
        : fIsRecursive(false), fRecSymbol(), fEnclosingLoop(encl), fSize(size) 
{}

/**
 * A loop with recursive dependencies can't be run alone. 
 * It must be included into another loop.
 * returns true is this loop has recursive dependencies.
 */
bool Loop::hasRecDependencies()                  
{ 
    return !fRecDependencies.empty(); 
}


/**
 * add a recursive dependency != fRecSymbol
 */
void Loop::addRecDependency(Tree t)
{
    if (t != fRecSymbol) {
        fRecDependencies.insert(t);
    }
}


/**
 * A loop is recursively dependent of t if
 * it is enclosed in a recursive loop defining t 
 */
bool Loop::isDependentOf(Tree t)
{
    Loop* l = this; //fEnclosing;
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
    tab(n,fout); fout << "for (int i = 0; i < " << fSize << "; i++) {";
    printlines(n+1, fExecCode, fout);
    if (fPostCode.size()>0) {
        tab(n+1,fout); fout << "// post processing";
        printlines(n+1, fPostCode, fout);
    }
    tab(n,fout); fout << "}";
}

// loop ordering

/**
 * Set the order of a loop and place it to appropriate set
 */
static void setOrder(Loop* l, int order, vector<lset>& V)
{
    V.resize(order+1);
    if (l->fOrder >= 0) { V[l->fOrder].erase(l); }
    l->fOrder = order; V[order].insert(l);
}

/**
 * Set the order of T1's instructions and collect there sons into T2
 */
static void setLevel(int order, const lset& T1, lset& T2, vector<lset>& V)
{
    for (lset::const_iterator p = T1.begin(); p!=T1.end(); p++) {
        setOrder(*p, order, V);
        T2.insert((*p)->fLoopDependencies.begin(), (*p)->fLoopDependencies.end());
    }
}

/**
 * Define the order number of a set of instructions starting from 0
 * and collect them in a vector of sets
 */
void orderInstructions(const lvec& S, vector<lset>& V)
{
    lset            T1, T2;
    int             level;
    
    //cout << "START ordering" << endl;
    T1.insert(S.begin(), S.end()); level=0; V.clear();
    do {
        setLevel(level, T1, T2, V); 
        T1=T2; T2.clear(); level++;
    } while (T1.size()>0);
    //cout << "END ordering " << level << endl;
}
