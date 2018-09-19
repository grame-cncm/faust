#include "loop.hh"
#include "Text.hh"

extern bool gVectorSwitch;
extern bool gOpenMPSwitch;
extern bool gOpenMPLoop;

using namespace std;

/**
 * Print n tabs (for indentation purpose)
 * @param n number of tabs to print
 * @param fout output stream
 */
static void tab(int n, ostream &fout)
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
static void printlines(int n, list<string> &lines, ostream &fout)
{
    string curr = "NONE";  // at first, no if-statement open
    for (auto s : lines) {
        string cond, body;
        if (isIfExpression(s, cond, body)) {
            // We have a conditional statement
            if (cond != curr) {
                // with a different condition from the current one
                if (curr != "NONE") {
                    // There is a previously open if-statement that we need to close
                    tab(n, fout);
                    fout << "}";
                }
                // we need to open a new if-statement
                tab(n, fout);
                fout << "if (" << cond << ") {";
            }
            tab(n + 1, fout);
            fout << body;
            curr = cond;
        } else {
            // we have an unconditional statement
            if (curr != "NONE") {
                // There is a previously open if-statement that we need to close
                tab(n, fout);
                fout << "}";
                curr = "NONE";
            }
            tab(n, fout);
            fout << s;
        }
    }
    if (curr != "NONE") {
        // There is a previously open if-statement that we need to close
        tab(n, fout);
        fout << "}";
        curr = "NONE";
    }
}

/**
 * Create a recursive loop
 * @param recsymbol the recursive symbol defined in this loop
 * @param encl the enclosing loop
 * @param size the number of iterations of the loop
 */
Loop::Loop(Tree recsymbol, Loop *encl, const string &size)
    : fIsRecursive(true),
      fCommonRate(1),
      fRecSymbolSet(singleton(recsymbol)),
      fEnclosingLoop(encl),
      fSize(size),
      fOrder(-1),
      fIndex(-1),
      fUseCount(0),
      fPrinted(0)
{
}

/**
 * Create a non recursive loop
 * @param encl the enclosing loop
 * @param size the number of iterations of the loop
 */
Loop::Loop(Loop *encl, const string &size)
    : fIsRecursive(false),
      fCommonRate(1),
      fRecSymbolSet(nil),
      fEnclosingLoop(encl),
      fSize(size),
      fOrder(-1),
      fIndex(-1),
      fUseCount(0),
      fPrinted(0)
{
}

/**
 * A loop with recursive dependencies can't be run alone.
 * It must be included into another loop.
 * returns true is this loop has recursive dependencies
 * and must be included in an enclosing loop
 */

bool Loop::hasRecDependencyIn(Tree S)
{
    Loop *l = this;
    while (l && isNil(setIntersection(l->fRecSymbolSet, S))) l = l->fEnclosingLoop;
    return l != 0;
}

/**
 * Test if a loop is empty that is if it contains no lines of code).
 * @return true if the loop is empty
 */
bool Loop::isEmpty()
{
    return fPreCode.empty() && fExecCode.empty() && fPostCode.empty() && (fExtraLoops.begin() == fExtraLoops.end());
}

/**
 * Add a line of pre code  (begin of the loop)
 */
void Loop::addPreCode(const string &str)
{
    // cerr << this << "->addExecCode " << str << endl;
    fPreCode.push_back(str);
}

/**
 * Add a line of pre code  (begin of the loop)
 */
void Loop::setCommonRate(int rate)
{
    fCommonRate = rate;
}

/**
 * Add a line of exec code
 */
void Loop::addExecCode(const string &str)
{
    cerr << this << "->addExecCode " << str << endl;
    string cond;
    string body;
    (void)isIfExpression(str, cond, body);
    fExecCode.push_back(str);
}

/**
 * Add a line of post exec code (end of the loop)
 */
void Loop::addPostCode(const string &str)
{
    // cerr << this << "->addPostCode " << str << endl;
    fPostCode.push_front(str);
}

/**
 * Absorb a loop by copying its recursive dependencies, its loop dependencies
 * and its lines of exec and post exec code.
 * @param l the Loop to be absorbed
 */
void Loop::absorb(Loop *l)
{
    // the loops must have the same number of iterations
    assert(fSize == l->fSize);
    fRecSymbolSet = setUnion(fRecSymbolSet, l->fRecSymbolSet);

    // update loop dependencies by adding those from the absorbed loop
    fBackwardLoopDependencies.insert(l->fBackwardLoopDependencies.begin(), l->fBackwardLoopDependencies.end());

    // add the line of code of the absorbed loop
    fPreCode.insert(fPreCode.end(), l->fPreCode.begin(), l->fPreCode.end());
    fExecCode.insert(fExecCode.end(), l->fExecCode.begin(), l->fExecCode.end());
    fPostCode.insert(fPostCode.begin(), l->fPostCode.begin(), l->fPostCode.end());
}

/**
 * Print a loop (unless it is empty)
 * @param n number of tabs of indentation
 * @param fout output stream
 */
void Loop::println(int n, ostream &fout)
{
    for (list<Loop *>::const_iterator s = fExtraLoops.begin(); s != fExtraLoops.end(); s++) {
        (*s)->println(n, fout);
    }

    if (fPreCode.size() + fExecCode.size() + fPostCode.size() > 0) {
        /*        if (gVectorSwitch) {
tab(n,fout);
fout << ((fIsRecursive) ? "// recursive loop" : "// vectorizable loop");
}*/

        tab(n, fout);
        fout << "// LOOP " << this;
        if (fPreCode.size() > 0) {
            tab(n, fout);
            fout << "// pre processing";
            printlines(n, fPreCode, fout);
        }

        tab(n, fout);
        fout << "// exec code";
        tab(n, fout);
        fout << "for (int i=0; i<" << fSize << "; i++) {";
        printlines(n + 1, fExecCode, fout);
        tab(n, fout);
        fout << "}";

        if (fPostCode.size() > 0) {
            tab(n, fout);
            fout << "// post processing";
            printlines(n, fPostCode, fout);
        }
        tab(n, fout);
    }
}

/**
 * Print a parallel loop (unless it is empty). Should be called only for loop
 * without pre and post processing
 * @param n number of tabs of indentation
 * @param fout output stream
 */
void Loop::printParLoopln(int n, ostream &fout)
{
    for (list<Loop *>::const_iterator s = fExtraLoops.begin(); s != fExtraLoops.end(); s++) {
        tab(n, fout);
        fout << "#pragma omp single";
        tab(n, fout);
        fout << "{";
        (*s)->println(n + 1, fout);
        tab(n, fout);
        fout << "}";
    }

    if (fPreCode.size() + fExecCode.size() + fPostCode.size() > 0) {
        tab(n, fout);
        fout << "// LOOP " << this;
        if (fPreCode.size() > 0) {
            tab(n, fout);
            fout << "#pragma omp single";
            tab(n, fout);
            fout << "{";
            tab(n + 1, fout);
            fout << "// pre processing";
            printlines(n + 1, fPreCode, fout);
            tab(n, fout);
            fout << "}";
        }

        tab(n, fout);
        fout << "// exec code";
        tab(n, fout);
        fout << "#pragma omp for";
        tab(n, fout);
        fout << "for (int i=0; i<" << fSize << "; i++) {";
        printlines(n + 1, fExecCode, fout);
        tab(n, fout);
        fout << "}";

        if (fPostCode.size() > 0) {
            tab(n, fout);
            fout << "#pragma omp single";
            tab(n, fout);
            fout << "{";
            tab(n + 1, fout);
            fout << "// post processing";
            printlines(n + 1, fPostCode, fout);
            tab(n, fout);
            fout << "}";
        }
        tab(n, fout);
    }
}

/**
 * Print a single loop (unless it is empty)
 * @param n number of tabs of indentation
 * @param fout output stream
 */
void Loop::printoneln(int n, ostream &fout)
{
    if (fPreCode.size() + fExecCode.size() + fPostCode.size() > 0) {
        /*        if (gVectorSwitch) {
tab(n,fout);
fout << ((fIsRecursive) ? "// recursive loop" : "// vectorizable loop");
}*/

        if (fCommonRate == 1) {
            tab(n, fout);
            fout << "for (int i=0; i<" << fSize << "; i++) {";
        } else {
            tab(n, fout);
            fout << "for (int i=0; i<" << fSize << "*" << fCommonRate << "; i++) {";
        }
        if (fPreCode.size() > 0) {
            tab(n + 1, fout);
            fout << "// pre processing";
            printlines(n + 1, fPreCode, fout);
        }
        printlines(n + 1, fExecCode, fout);
        if (fPostCode.size() > 0) {
            tab(n + 1, fout);
            fout << "// post processing";
            printlines(n + 1, fPostCode, fout);
        }
        tab(n, fout);
        fout << "}";
    }
}

//-------------------------------------------------------
void Loop::concat(Loop *l)
{
    assert(l->fUseCount == 1);
    assert(fBackwardLoopDependencies.size() == 1);
    assert((*fBackwardLoopDependencies.begin()) == l);

    fExtraLoops.push_front(l);
    fBackwardLoopDependencies = l->fBackwardLoopDependencies;
}
