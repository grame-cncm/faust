/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

/**********************************************************************
        - klass.cpp : class C++ to be filled (FAUST project) -

        History :
        -----------
        17-10-2001 : initial implementation  (yo)
        18-10-2001 : add getFreshID (yo)
        02-11-2001 : add sub-classes (yo)
        06-11-2001 : change classers impression (yo)

***********************************************************************/

#include <stdio.h>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

#include "Text.hh"
#include "floats.hh"
#include "klass.hh"
#include "recursivness.hh"
#include "signals.hh"
#include "uitree.hh"
#include "global.hh"

using namespace std;

static int gTaskCount = 0;

bool Klass::fNeedPowerDef = false;

/**
 * Store the loop used to compute a signal
 */
void Klass::setLoopProperty(Tree sig, Loop* l)
{
    fLoopProperty.set(sig, l);
}

/**
 * Returns the loop used to compute a signal
 */
bool Klass::getLoopProperty(Tree sig, Loop*& l)
{
    return fLoopProperty.get(sig, l);
}

/**
 * Open a non-recursive loop on top of the stack of open loops.
 * @param size the number of iterations of the loop
 */
void Klass::openLoop(const string& size)
{
    fTopLoop = new Loop(fTopLoop, size);
    // cerr << "\nOPEN SHARED LOOP(" << size << ") ----> " << fTopLoop << endl;
}

/**
 * Open a recursive loop on top of the stack of open loops.
 * @param recsymbol the recursive symbol defined in this loop
 * @param size the number of iterations of the loop
 */
void Klass::openLoop(Tree recsymbol, const string& size)
{
    fTopLoop = new Loop(recsymbol, fTopLoop, size);
    // cerr << "\nOPEN REC LOOP(" << *recsymbol << ", " << size << ") ----> " << fTopLoop << endl;
}

void Klass::listAllLoopProperties(Tree sig, set<Loop*>& L, set<Tree, treeorder>& visited)
{
    if (visited.count(sig) == 0) {
        visited.insert(sig);
        Loop* l;
        if (getLoopProperty(sig, l)) {
            L.insert(l);
        } else {
            // we go down the expression
            tvec subsigs;
            int  n = getSubSignals(sig, subsigs, false);
            for (int i = 0; i < n; i++) {
                listAllLoopProperties(subsigs[i], L, visited);
            }
        }
    }
}

/**
 * Close the top loop and either keep it
 * or absorb it within its enclosing loop.
 */
void Klass::closeLoop(Tree sig)
{
    faustassert(fTopLoop);

    // fix the missing dependencies
    set<Loop*> L;
    set<Tree, treeorder>  V;
    listAllLoopProperties(sig, L, V);
    for (Loop* l : L) {
        fTopLoop->fBackwardLoopDependencies.insert(l);
    }

    Loop* l  = fTopLoop;
    fTopLoop = l->fEnclosingLoop;
    faustassert(fTopLoop);

    // l->println(4, cerr);
    // cerr << endl;

    Tree S = symlist(sig);
    // cerr << "CLOSE LOOP :" << l << " with symbols " << *S << endl;
    if (l->isEmpty() || fTopLoop->hasRecDependencyIn(S)) {
        // cout << " will absorb" << endl;
        // empty or dependent loop -> absorbed by enclosing one
        // cerr << "absorbed by : " << fTopLoop << endl;
        fTopLoop->absorb(l);
        // delete l; HACK !!!
    } else {
        // cout << " will NOT absorb" << endl;
        // we have an independent loop
        setLoopProperty(sig, l);  // associate the signal
        fTopLoop->fBackwardLoopDependencies.insert(l);
        // we need to indicate that all recursive symbols defined
        // in this loop are defined in this loop
        for (Tree lsym = l->fRecSymbolSet; !isNil(lsym); lsym = tl(lsym)) {
            this->setLoopProperty(hd(lsym), l);
            // cerr << "loop " << l << " defines " << *hd(lsym) << endl;
        }
    }
    // cerr << "\n" << endl;
}

/**
 * Print a list of elements (e1, e2,...)
 */
static void printdecllist(int n, const string& decl, list<string>& content, ostream& fout)
{
    if (!content.empty()) {
        fout << "\\";
        tab(n, fout);
        fout << decl;
        string sep = "(";
        for (const auto& s : content) {
            fout << sep << s;
            sep = ", ";
        }
        fout << ')';
    }
}

/**
 * Print the required C++ libraries as comments in source code
 */
void Klass::printLibrary(ostream& fout)
{
    set<string>           S;
    set<string>::iterator f;

    string sep;
    collectLibrary(S);
    fout << "/* link with ";
    for (f = S.begin(), sep = ": "; f != S.end(); f++, sep = ", ") {
        fout << sep << *f;
    }
    fout << " */\n";
}

/**
 * Print the required include files
 */
void Klass::printIncludeFile(ostream& fout)
{
    if (gGlobal->gOpenMPSwitch) {
        fout << "#include <omp.h>\n";
    }

    set<string> S;
    collectIncludeFile(S);
    for (const auto& f : S) {
        string inc = f;
        // Only print non-empty include (inc is actually quoted)
        if (inc.size() > 2) {
            fout << "#include " << f << "\n";
        }
    }
}

/**
 * Print additional functions required by the generated code
 */

void Klass::printAdditionalCode(ostream& fout)
{
    fout << "#ifndef FAUSTMAXI" << endl;
    fout << "#define FAUSTMAXI" << endl;
    fout << "static inline int faustmaxi(int a, int b) { return (a > b) ? a : b; }" << endl;
    fout << "static inline int faustmini(int a, int b) { return (a < b) ? a : b; }" << endl;
    fout << "#endif" << endl;

    if (fNeedPowerDef) {
        // Add faustpower definition to C++ code
        fout << "#ifndef FAUSTPOWER" << endl;
        fout << "#define FAUSTPOWER" << endl;
        fout << "#include <cmath>" << endl;

        fout << "template <int N> inline int faustpower(int x)              { return "
                "faustpower<N/2>(x) * "
                "faustpower<N-N/2>(x); } "
             << endl;
        fout << "template <> 	 inline int faustpower<0>(int x)            { return 1; }" << endl;
        fout << "template <> 	 inline int faustpower<1>(int x)            { return x; }" << endl;
        fout << "template <> 	 inline int faustpower<2>(int x)            { return x*x; }"
             << endl;

        if (gGlobal->gFloatSize == 1) {
            fout << "template <int N> inline float faustpower(float x)            { return "
                    "faustpower<N/2>(x) * "
                    "faustpower<N-N/2>(x); } "
                 << endl;
            fout << "template <> 	 inline float faustpower<0>(float x)          { return 1; }"
                 << endl;
            fout << "template <> 	 inline float faustpower<1>(float x)          { return x; }"
                 << endl;
            fout << "template <> 	 inline float faustpower<2>(float x)          { return x*x; }"
                 << endl;

        } else if (gGlobal->gFloatSize == 2) {
            fout << "template <int N> inline double faustpower(double x)          { return "
                    "faustpower<N/2>(x) * "
                    "faustpower<N-N/2>(x); } "
                 << endl;
            fout << "template <> 	 inline double faustpower<0>(double x)        { return 1; }"
                 << endl;
            fout << "template <> 	 inline double faustpower<1>(double x)        { return x; }"
                 << endl;
            fout << "template <> 	 inline double faustpower<2>(double x)        { return x*x; }"
                 << endl;

        } else if (gGlobal->gFloatSize == 3) {
            fout << "template <int N> inline long double faustpower(long double x){ return "
                    "powl(x,N); }"
                 << endl;
        }
        fout << "#endif" << endl;
    }
}

/**
 * Print metadata declaration
 */
void Klass::printMetadata(int n, const MetaDataSet& S, ostream& fout)
{
    tab(n, fout);
    fout << "virtual void metadata(Meta* m) { ";

    // We do not want to accumulate metadata from all hierachical levels, so the upper level only is
    // kept
    for (const auto& i : gGlobal->gMetaDataSet) {
        if (i.first != tree("author")) {
            tab(n + 1, fout);
            fout << "m->declare(\"" << *(i.first) << "\", " << **(i.second.begin()) << ");";
        } else {
            // But the "author" meta data is accumulated, the upper level becomes the main author
            // and sub-levels become "contributor"
            for (const auto& j : i.second) {
                if (j == *i.second.begin()) {
                    tab(n + 1, fout);
                    fout << "m->declare(\"" << *(i.first) << "\", " << *j << ");";
                } else {
                    tab(n + 1, fout);
                    fout << "m->declare(\""
                         << "contributor"
                         << "\", " << *j << ");";
                }
            }
        }
    }

    tab(n, fout);
    fout << "}" << endl;
}

inline bool isElement(const set<Loop*>& S, Loop* l)
{
    return S.find(l) != S.end();
}

/**
 * Print a loop graph deep first
 */
void Klass::printLoopDeepFirst(int n, ostream& fout, Loop* l, set<Loop*>& visited)
{
    // avoid printing already printed loops
    if (isElement(visited, l)) {
        return;
    }

    // remember we have printed this loop
    visited.insert(l);

    // print the dependencies loops (that need to be computed before this one)
    for (lset::const_iterator p = l->fBackwardLoopDependencies.begin();
         p != l->fBackwardLoopDependencies.end(); p++) {
        printLoopDeepFirst(n, fout, *p, visited);
    }
    // the print the loop itself
    tab(n, fout);
    tab(n, fout);
    fout << "// LOOP " << l << ", ORDER " << l->fOrder << endl;
    l->println(n + 1, fout);
}

/**
 * Compute how many time each loop is used in a DAG
 */
static void computeUseCount(Loop* l)
{
    l->fUseCount++;
    if (l->fUseCount == 1) {
        for (lset::iterator p = l->fBackwardLoopDependencies.begin();
             p != l->fBackwardLoopDependencies.end(); p++) {
            computeUseCount(*p);
        }
    }
}

/**
 * Group together sequences of loops
 */
static void groupSeqLoops(Loop* l, set<Loop*>& visited)
{
    if (visited.find(l) == visited.end()) {
        visited.insert(l);
        int n = (int)l->fBackwardLoopDependencies.size();
        if (n == 0) {
            return;
        } else if (n == 1) {
            Loop* f = *(l->fBackwardLoopDependencies.begin());
            if (f->fUseCount == 1) {
                l->concat(f);
                groupSeqLoops(l, visited);
            } else {
                groupSeqLoops(f, visited);
            }
            return;
        } else if (n > 1) {
            for (lset::iterator p = l->fBackwardLoopDependencies.begin();
                 p != l->fBackwardLoopDependencies.end(); p++) {
                groupSeqLoops(*p, visited);
            }
        }
    }
}

#define WORK_STEALING_INDEX 0
#define LAST_TASK_INDEX 1
#define START_TASK_INDEX LAST_TASK_INDEX + 1

#define START_TASK_MAX 2

void Klass::buildTasksList()
{
    lgraph G;

    if (gGlobal->gGroupTaskSwitch) {
        computeUseCount(fTopLoop);
        set<Loop*> visited;
        groupSeqLoops(fTopLoop, visited);
    }

    sortGraph(fTopLoop, G);
    int index_task = START_TASK_INDEX;

    addDeclCode("TaskGraph fGraph;");
    addDeclCode("FAUSTFLOAT** input;");
    addDeclCode("FAUSTFLOAT** output;");
    addDeclCode("volatile bool fIsFinished;");
    addDeclCode("int fCount;");
    addDeclCode("int fIndex;");
    addDeclCode("DSPThreadPool* fThreadPool;");
    addDeclCode("int fStaticNumThreads;");
    addDeclCode("int fDynamicNumThreads;");

    // Compute forward dependencies
    for (int l = (int)G.size() - 1; l >= 0; l--) {
        for (lset::const_iterator p = G[l].begin(); p != G[l].end(); p++) {
            for (lset::const_iterator p1 = (*p)->fBackwardLoopDependencies.begin();
                 p1 != (*p)->fBackwardLoopDependencies.end(); p1++) {
                (*p1)->fForwardLoopDependencies.insert((*p));
            }
            (*p)->fIndex = index_task;
            index_task++;
        }
    }

    // Compute ready tasks list
    vector<int> task_num;
    for (int l = (int)G.size() - 1; l >= 0; l--) {
        lset::const_iterator next;
        for (lset::const_iterator p = G[l].begin(); p != G[l].end(); p++) {
            if ((*p)->fBackwardLoopDependencies.size() == 0) {
                task_num.push_back((*p)->fIndex);
            }
        }
    }

    if (task_num.size() < START_TASK_MAX) {
        // Push ready tasks thread 0, execute one task directly

        addZone3("if (cur_thread == 0) {");

        Loop* keep = NULL;
        for (int l = (int)G.size() - 1; l >= 0; l--) {
            lset::const_iterator next;
            for (lset::const_iterator p = G[l].begin(); p != G[l].end(); p++) {
                if ((*p)->fBackwardLoopDependencies.size() == 0) {
                    if (keep == NULL) {
                        keep = *p;
                    } else {
                        addZone3(subst("    taskqueue.PushHead($0);", T((*p)->fIndex)));
                    }
                }
            }
        }

        if (keep != NULL) {
            addZone3(subst("    tasknum = $0;", T(keep->fIndex)));
        }

        addZone3("} else {");
        addZone3("    tasknum = TaskQueue::GetNextTask(cur_thread, fDynamicNumThreads);");
        addZone3("}");

    } else {
        // Cut ready tasks list and have each thread (dynamically) use a subpart
        addZone3(subst("int task_list_size = $0;", T((int)task_num.size())));
        stringstream buf;
        buf << "int task_list[" << task_num.size() << "] = {";
        for (size_t i = 0; i < task_num.size(); i++) {
            buf << task_num[i];
            if (i != (task_num.size() - 1)) {
                buf << ",";
            }
        }
        buf << "};";

        addZone3(buf.str());
        addZone3(
            "taskqueue.InitTaskList(task_list_size, task_list, fDynamicNumThreads, cur_thread, "
            "tasknum);");
    }

    // Last stage connected to end task
    if (G[0].size() > 1) {
        addZone2c("// Initialize end task, if more than one input");
        addZone2c(subst("fGraph.InitTask($0,$1);", T(LAST_TASK_INDEX), T((int)G[0].size())));
    } else {
        addZone2c("// End task has only one input, so will be directly activated");
    }

    // Compute init section
    addZone2c("// Only initialize taks with more than one input");
    for (int l = (int)G.size() - 1; l >= 0; l--) {
        for (lset::const_iterator p = G[l].begin(); p != G[l].end(); p++) {
            if ((*p)->fBackwardLoopDependencies.size() >
                1) {  // Only initialize taks with more than 1 input, since
                      // taks with one input are "directly" activated.
                addZone2c(subst("fGraph.InitTask($0,$1);", T(START_TASK_INDEX + gTaskCount++),
                                T((int)(*p)->fBackwardLoopDependencies.size())));
            } else {
                gTaskCount++;
            }
        }
    }

    addInitCode("fStaticNumThreads = get_max_cpu();");
    addInitCode(
        "fDynamicNumThreads = getenv(\"OMP_NUM_THREADS\") ? atoi(getenv(\"OMP_NUM_THREADS\")) : "
        "fStaticNumThreads;");
    addInitCode("fThreadPool->StartAll(fStaticNumThreads - 1, false);");

    gTaskCount = 0;
}

/**
 * Print the loop graph (used for vector code)
 */
void Klass::printLoopGraphVector(int n, ostream& fout)
{
    if (gGlobal->gGroupTaskSwitch) {
        computeUseCount(fTopLoop);
        set<Loop*> visited;
        groupSeqLoops(fTopLoop, visited);
    }

    lgraph G;
    sortGraph(fTopLoop, G);

#if 1
    // EXPERIMENTAL
    if (gGlobal->gVectorSwitch && gGlobal->gDeepFirstSwitch) {
        set<Loop*> visited;
        printLoopDeepFirst(n, fout, fTopLoop, visited);
        return;
    }
#endif

    // normal mode
    for (int l = (int)G.size() - 1; l >= 0; l--) {
        if (gGlobal->gVectorSwitch) {
            tab(n, fout);
            fout << "// Section : " << G.size() - l;
        }
        for (lset::const_iterator p = G[l].begin(); p != G[l].end(); p++) {
            (*p)->println(n, fout);
        }
    }
}

/**
 * Print the loop graph as a serie of parallel loops
 */
void Klass::printLoopGraphOpenMP(int n, ostream& fout)
{
    if (gGlobal->gGroupTaskSwitch) {
        computeUseCount(fTopLoop);
        set<Loop*> visited;
        groupSeqLoops(fTopLoop, visited);
    }

    lgraph G;
    sortGraph(fTopLoop, G);

    // OpenMP mode : add OpenMP directives
    for (int l = (int)G.size() - 1; l >= 0; l--) {
        tab(n, fout);
        fout << "// Section : " << G.size() - l;
        printLoopLevelOpenMP(n, (int)G.size() - l, G[l], fout);
    }
}

/**
 * Print the loop graph as a serie of parallel loops
 */
void Klass::printLoopGraphScheduler(int n, ostream& fout)
{
    if (gGlobal->gGroupTaskSwitch) {
        computeUseCount(fTopLoop);
        set<Loop*> visited;
        groupSeqLoops(fTopLoop, visited);
    }

    lgraph G;
    sortGraph(fTopLoop, G);

    // OpenMP mode : add OpenMP directives
    for (int l = (int)G.size() - 1; l > 0; l--) {
        tab(n, fout);
        fout << "// Section : " << G.size() - l;
        printLoopLevelScheduler(n, (int)G.size() - l, G[l], fout);
    }

    printLastLoopLevelScheduler(n, (int)G.size(), G[0], fout);
}

/**
 * Print the loop graph in dot format
 */
void Klass::printGraphDotFormat(ostream& fout)
{
    lgraph G;
    sortGraph(fTopLoop, G);

    fout << "strict digraph loopgraph {" << endl;
    fout << '\t' << "rankdir=LR;" << endl;
    fout << '\t' << "node[color=blue, fillcolor=lightblue, style=filled, fontsize=9];" << endl;

    int lnum = 0;  // used for loop numbers
    // for each level of the graph
    for (int l = (int)G.size() - 1; l >= 0; l--) {
        // for each task in the level
        for (lset::const_iterator t = G[l].begin(); t != G[l].end(); t++) {
            // print task label "Lxxx : 0xffffff"
            fout << '\t' << 'L' << (*t) << "[label=<<font face=\"verdana,bold\">L" << lnum++
                 << "</font> : " << (*t) << ">];" << endl;
            // for each source of the task
            for (lset::const_iterator src = (*t)->fBackwardLoopDependencies.begin();
                 src != (*t)->fBackwardLoopDependencies.end(); src++) {
                // print the connection Lxxx -> Lyyy;
                fout << '\t' << 'L' << (*src) << "->" << 'L' << (*t) << ';' << endl;
            }
        }
    }
    fout << "}" << endl;
}

/**
 * Print the loop graph (used for internals classes)
 */
void Klass::printLoopGraphInternal(int n, ostream& fout)
{
    lgraph G;
    sortGraph(fTopLoop, G);

    // normal mode
    for (int l = (int)G.size() - 1; l >= 0; l--) {
        if (gGlobal->gVectorSwitch) {
            tab(n, fout);
            fout << "// Section : " << G.size() - l;
        }
        for (lset::const_iterator p = G[l].begin(); p != G[l].end(); p++) {
            (*p)->printoneln(n, fout);
        }
    }
}

/**
 * Print the loop graph (scalar mode)
 */
void Klass::printLoopGraphScalar(int n, ostream& fout)
{
    fTopLoop->printoneln(n, fout);
}

/**
 * returns true if all the loops are non recursive
 */
static bool nonRecursiveLevel(const lset& L)
{
    for (lset::const_iterator p = L.begin(); p != L.end(); p++) {
        if ((*p)->fIsRecursive) {
            return false;
        }
    }
    return true;
}

/**
 * Print the 'level' of the loop graph as a set of
 * parallel loops
 */
void Klass::printLoopLevelOpenMP(int n, int lnum, const lset& L, ostream& fout)
{
    if (nonRecursiveLevel(L) && L.size() == 1) {
        for (lset::const_iterator p = L.begin(); p != L.end(); p++) {
            if ((*p)->isEmpty() == false) {
                if (gGlobal->gOpenMPLoop) {
                    (*p)->printParLoopln(n, fout);
                } else {
                    tab(n, fout);
                    fout << "#pragma omp single ";
                    tab(n, fout);
                    fout << "{ ";
                    (*p)->println(n + 1, fout);
                    tab(n, fout);
                    fout << "} ";
                }
            }
        }

    } else if (L.size() > 1) {
        tab(n, fout);
        fout << "#pragma omp sections ";
        tab(n, fout);
        fout << "{ ";
        for (lset::const_iterator p = L.begin(); p != L.end(); p++) {
            tab(n + 1, fout);
            fout << "#pragma omp section ";
            tab(n + 1, fout);
            fout << "{";
            (*p)->println(n + 2, fout);
            tab(n + 1, fout);
            fout << "} ";
        }
        tab(n, fout);
        fout << "} ";
    } else if (L.size() == 1 && !(*L.begin())->isEmpty()) {
        tab(n, fout);
        fout << "#pragma omp single ";
        tab(n, fout);
        fout << "{ ";
        for (lset::const_iterator p = L.begin(); p != L.end(); p++) {
            (*p)->println(n + 1, fout);
        }
        tab(n, fout);
        fout << "} ";
    }
}

/**
 * Print the 'level' of the loop graph as a set of
 * parallel loops
 */
void Klass::printLastLoopLevelScheduler(int n, int lnum, const lset& L, ostream& fout)
{
    if (nonRecursiveLevel(L) && L.size() == 1 && !(*L.begin())->isEmpty()) {
        lset::const_iterator p = L.begin();
        tab(n, fout);
        fout << "case " << gTaskCount++ << ": { ";
        (*p)->println(n + 1, fout);
        tab(n + 1, fout);
        fout << "tasknum = LAST_TASK_INDEX;";
        tab(n + 1, fout);
        fout << "break;";
        tab(n, fout);
        fout << "} ";

    } else if (L.size() > 1) {
        for (lset::const_iterator p = L.begin(); p != L.end(); p++) {
            tab(n, fout);
            fout << "case " << gTaskCount++ << ": { ";
            (*p)->println(n + 1, fout);
            tab(n + 1, fout);
            fout << "fGraph.ActivateOneOutputTask(taskqueue, LAST_TASK_INDEX, tasknum);";
            tab(n + 1, fout);
            fout << "break;";
            tab(n, fout);
            fout << "} ";
        }

    } else if (L.size() == 1 && !(*L.begin())->isEmpty()) {
        lset::const_iterator p = L.begin();
        tab(n, fout);
        fout << "case " << gTaskCount++ << ": { ";
        (*p)->println(n + 1, fout);
        tab(n + 1, fout);
        fout << "tasknum = LAST_TASK_INDEX;";
        tab(n + 1, fout);
        fout << "break;";
        tab(n, fout);
        fout << "} ";
    }
}

void Klass::printOneLoopScheduler(lset::const_iterator p, int n, ostream& fout)
{
    tab(n, fout);
    fout << "case " << gTaskCount++ << ": { ";
    (*p)->println(n + 1, fout);

    // One output only
    if ((*p)->fForwardLoopDependencies.size() == 1) {
        lset::const_iterator p1 = (*p)->fForwardLoopDependencies.begin();
        if ((*p1)->fBackwardLoopDependencies.size() == 1) {
            tab(n + 1, fout);
            fout << subst("tasknum = $0;", T((*p1)->fIndex));
        } else {
            tab(n + 1, fout);
            fout << subst("fGraph.ActivateOneOutputTask(taskqueue, $0, tasknum);",
                          T((*p1)->fIndex));
        }

    } else {
        Loop* keep = NULL;
        // Find one output with only one backward dependencies
        for (lset::const_iterator p1 = (*p)->fForwardLoopDependencies.begin();
             p1 != (*p)->fForwardLoopDependencies.end(); p1++) {
            if ((*p1)->fBackwardLoopDependencies.size() == 1) {
                keep = *p1;
                break;
            }
        }

        if (keep == NULL) {
            tab(n + 1, fout);
            fout << "tasknum = WORK_STEALING_INDEX;";
        }

        for (lset::const_iterator p1 = (*p)->fForwardLoopDependencies.begin();
             p1 != (*p)->fForwardLoopDependencies.end(); p1++) {
            if ((*p1)->fBackwardLoopDependencies.size() == 1) {  // Task is the only input
                if (*p1 != keep) {
                    tab(n + 1, fout);
                    fout << subst("taskqueue.PushHead($0);", T((*p1)->fIndex));
                }
            } else {
                if (keep == NULL) {
                    tab(n + 1, fout);
                    fout << subst("fGraph.ActivateOutputTask(taskqueue, $0, tasknum);",
                                  T((*p1)->fIndex));
                } else {
                    tab(n + 1, fout);
                    fout << subst("fGraph.ActivateOutputTask(taskqueue, $0);", T((*p1)->fIndex));
                }
            }
        }

        if (keep != NULL) {
            tab(n + 1, fout);
            fout << subst("tasknum = $0;", T(keep->fIndex));  // Last one
        } else {
            tab(n + 1, fout);
            fout << "fGraph.GetReadyTask(taskqueue, tasknum);";  // Last one
        }
    }

    tab(n + 1, fout);
    fout << "break;";
    tab(n, fout);
    fout << "} ";
}

/**
 * Print the 'level' of the loop graph as a set of
 * parallel loops
 */

void Klass::printLoopLevelScheduler(int n, int lnum, const lset& L, ostream& fout)
{
    if (nonRecursiveLevel(L) && L.size() == 1 && !(*L.begin())->isEmpty()) {
        printOneLoopScheduler(L.begin(), n, fout);
    } else if (L.size() > 1) {
        for (lset::const_iterator p = L.begin(); p != L.end(); p++) {
            printOneLoopScheduler(p, n, fout);
        }
    } else if (L.size() == 1 && !(*L.begin())->isEmpty()) {
        printOneLoopScheduler(L.begin(), n, fout);
    }
}

/**
 * Print a full C++ class corresponding to a Faust dsp
 */
void Klass::println(int n, ostream& fout)
{
    list<Klass*>::iterator k;

    tab(n, fout);
    fout << "#ifndef FAUSTCLASS " << endl;
    fout << "#define FAUSTCLASS " << fKlassName << endl;
    fout << "#endif" << endl;

    if (gGlobal->gSchedulerSwitch) {
        tab(n, fout);
        fout << "class " << fKlassName << " : public " << fSuperKlassName << ", public Runnable {";
    } else {
        tab(n, fout);
        fout << "class " << fKlassName << " : public " << fSuperKlassName << " {";
    }

    if (gGlobal->gUIMacroSwitch) {
        tab(n, fout);
        fout << "  public:";
    } else {
        tab(n, fout);
        fout << "  private:";
    }

    for (k = fSubClassList.begin(); k != fSubClassList.end(); k++) {
        (*k)->println(n + 1, fout);
    }

    printlines(n + 1, fDeclCode, fout);

    tab(n + 1, fout);
    fout << "int fSampleRate;\n";

    tab(n, fout);
    fout << "  public:";

    if (gGlobal->gMemoryManager >= 0) {
        tab(n + 1, fout);
        fout << "static dsp_memory_manager* fManager;" << endl;
    }

    printMetadata(n + 1, gGlobal->gMetaDataSet, fout);

    if (gGlobal->gSchedulerSwitch) {
        tab(n + 1, fout);
        fout << fKlassName << "() { "
             << "fThreadPool = DSPThreadPool::Init(); }";

        tab(n + 1, fout);
        fout << "virtual ~" << fKlassName << "() { "
             << "DSPThreadPool::Destroy(); }";
    }

    tab(n + 1, fout);
    fout << "virtual int getNumInputs() { "
         << "return " << fNumInputs << "; }";

    tab(n + 1, fout);
    fout << "virtual int getNumOutputs() { "
         << "return " << fNumOutputs << "; }";

    tab(n + 1, fout);
    fout << "static void classInit(int sample_rate) {";
    printlines(n + 2, fStaticInitCode, fout);
    tab(n + 1, fout);
    fout << "}";

    if (gGlobal->gMemoryManager >= 0) {
        tab(n + 1, fout);
        fout << "static void classDestroy() {";
        printlines(n + 2, fStaticDestroyCode, fout);
        tab(n + 1, fout);
        fout << "}";
    }

    tab(n + 1, fout);
    fout << "virtual void instanceConstants(int sample_rate) {";
    tab(n + 2, fout);
    fout << "fSampleRate = sample_rate;";
    printlines(n + 2, fInitCode, fout);
    tab(n + 1, fout);
    fout << "}";

    tab(n + 1, fout);
    fout << "virtual void instanceResetUserInterface() {";
    printlines(n + 2, fInitUICode, fout);
    tab(n + 1, fout);
    fout << "}";

    tab(n + 1, fout);
    fout << "virtual void instanceClear() {";
    printlines(n + 2, fClearCode, fout);
    tab(n + 1, fout);
    fout << "}";

    if (gGlobal->gMemoryManager >= 0) {
        tab(n + 1, fout);
        fout << "virtual void init(int sample_rate) {}";
    } else {
        tab(n + 1, fout);
        fout << "virtual void init(int sample_rate) {";
        tab(n + 2, fout);
        fout << "classInit(sample_rate);";
        tab(n + 2, fout);
        fout << "instanceInit(sample_rate);";
        tab(n + 1, fout);
        fout << "}";
    }

    tab(n + 1, fout);
    fout << "virtual void instanceInit(int sample_rate) {";
    tab(n + 2, fout);
    fout << "instanceConstants(sample_rate);";
    tab(n + 2, fout);
    fout << "instanceResetUserInterface();";
    tab(n + 2, fout);
    fout << "instanceClear();";
    tab(n + 1, fout);
    fout << "}";

    tab(n + 1, fout);
    fout << "virtual " << fKlassName << "* clone() {";
    tab(n + 2, fout);
    fout << "return new " << fKlassName << "();";
    tab(n + 1, fout);
    fout << "}";

    tab(n + 1, fout);
    fout << "virtual int getSampleRate() {";
    tab(n + 2, fout);
    fout << "return fSampleRate;";
    tab(n + 1, fout);
    fout << "}";

    tab(n + 1, fout);
    fout << "virtual void buildUserInterface(UI* ui_interface) {";
    printlines(n + 2, fUICode, fout);
    tab(n + 1, fout);
    fout << "}";

    printComputeMethod(n, fout);

    tab(n, fout);
    fout << "};\n" << endl;

    printlines(n, fStaticFields, fout);

    if (gGlobal->gMemoryManager >= 0) {
        tab(n, fout);
        fout << "dsp_memory_manager* " << fKlassName << "::fManager = 0;" << endl;
    }

    // generate user interface macros if needed
    if (gGlobal->gUIMacroSwitch) {
        tab(n, fout);
        fout << "#ifdef FAUST_UIMACROS";
        tab(n + 1, fout);
        tab(n + 1, fout);
        for (const auto& it : gGlobal->gMetaDataSet) {
            if (it.first == tree("filename")) {
                fout << "#define FAUST_FILE_NAME " << **(it.second.begin());
                break;
            }
        }
        tab(n + 1, fout);
        fout << "#define FAUST_CLASS_NAME "
             << "\"" << fKlassName << "\"";
        tab(n + 1, fout);
        fout << "#define FAUST_COMPILATION_OPIONS \"" << gGlobal->printCompilationOptions1()
             << "\"";
        tab(n + 1, fout);
        fout << "#define FAUST_INPUTS " << fNumInputs;
        tab(n + 1, fout);
        fout << "#define FAUST_OUTPUTS " << fNumOutputs;
        tab(n + 1, fout);
        fout << "#define FAUST_ACTIVES " << fNumActives;
        tab(n + 1, fout);
        fout << "#define FAUST_PASSIVES " << fNumPassives;
        printlines(n + 1, fUIMacro, fout);
        tab(n, fout);
        fout << "#endif" << endl;
    }

    fout << endl;
}

/**
 * Print Compute() method according to the various switch
 */
void Klass::printComputeMethod(int n, ostream& fout)
{
    if (gGlobal->gSchedulerSwitch) {
        printComputeMethodScheduler(n, fout);
    } else if (gGlobal->gOpenMPSwitch) {
        printComputeMethodOpenMP(n, fout);
    } else if (gGlobal->gLoopSplit) {
        // super-node emission builds its own inner loops and handles partial
        // chunks itself: it needs the scalar-block skeleton (whose Zone3Post
        // carries the buffer shifts) even under -vec
        printComputeMethodScalarBlock(n, fout);
    } else if (gGlobal->gVectorSwitch) {
        switch (gGlobal->gVectorLoopVariant) {
            case 0:
                printComputeMethodVectorFaster(n, fout);
                break;
            case 1:
                printComputeMethodVectorSimple(n, fout);
                break;
            default: {
                stringstream error;
                error << "ERROR : unknown loop variant" << gGlobal->gVectorLoopVariant << endl;
                throw faustexception(error.str());
            }
        }
    } else {
        printComputeMethodScalarBlock(n, fout);
    }
}

// ---- the call-sink pass ------------------------------------------------
// A libm call scheduled early in the loop body keeps every later-defined
// value live across the call, and the AArch64 convention makes nearly all
// NEON registers caller-saved : each such live is a spill/reload pair
// around the call, per sample, on the carried chains (granulator : the
// SAME expf with the SAME arguments costs 10.6 ns/sample emitted early
// against 2.3 emitted late). The pass sinks each unconditional
// libm-defining temp, together with the pure temps chained on it, down
// to its first real consumer ; any statement writing one of the group's
// inputs is a barrier. String-level like its neighbours above : verify
// everything or move nothing.

static const char* kLibmNames[] = {"expf", "logf", "log10f", "powf", "tanf", "sinf", "cosf",
                                   "tanhf", "sinhf", "coshf", "asinf", "acosf", "atanf",
                                   "atan2f", "fmodf", "remainderf", "exp", "log", "log10",
                                   "pow", "tan", "sin", "cos", "tanh", "sinh", "cosh",
                                   "asin", "acos", "atan", "atan2", "fmod", "remainder"};

static bool hasLibmCall(const std::string& code)
{
    for (const char* name : kLibmNames) {
        size_t len = strlen(name);
        size_t p   = 0;
        while ((p = code.find(name, p)) != std::string::npos) {
            bool bounded = (p == 0) || (!isalnum((unsigned char)code[p - 1]) && code[p - 1] != '_');
            if (bounded && p + len < code.size() && code[p + len] == '(') {
                return true;
            }
            p += len;
        }
    }
    return false;
}

static void collectIdents(const std::string& code, std::set<std::string>& out)
{
    size_t p = 0;
    while (p < code.size()) {
        if (isalpha((unsigned char)code[p]) || code[p] == '_') {
            size_t q = p;
            while (q < code.size() && (isalnum((unsigned char)code[q]) || code[q] == '_')) {
                q++;
            }
            out.insert(code.substr(p, q - p));
            p = q;
        } else {
            p++;
        }
    }
}

// accepts "[type \t]IDENT[optional [..]] = ..." ; lhs receives IDENT
static bool parseWriteTarget(const std::string& code, std::string& lhs, bool& isDecl)
{
    size_t p = 0;
    while (p < code.size() && isspace((unsigned char)code[p])) {
        p++;
    }
    isDecl = false;
    for (const char* ty : {"float", "double", "int"}) {
        size_t len = strlen(ty);
        if (code.compare(p, len, ty) == 0 && p + len < code.size() &&
            isspace((unsigned char)code[p + len])) {
            p += len;
            while (p < code.size() && isspace((unsigned char)code[p])) {
                p++;
            }
            isDecl = true;
            break;
        }
    }
    size_t q = p;
    while (q < code.size() && (isalnum((unsigned char)code[q]) || code[q] == '_')) {
        q++;
    }
    if (q == p) {
        return false;
    }
    lhs = code.substr(p, q - p);
    if (q < code.size() && code[q] == '[') {
        int depth = 1;
        q++;
        while (q < code.size() && depth) {
            if (code[q] == '[') {
                depth++;
            }
            if (code[q] == ']') {
                depth--;
            }
            q++;
        }
        isDecl = false;  // an indexed write is a store, never a fresh temp
    }
    while (q < code.size() && isspace((unsigned char)code[q])) {
        q++;
    }
    return q + 1 < code.size() && code[q] == '=' && code[q + 1] != '=';
}

void Klass::sinkExpensiveCalls()
{
    if (getenv("FAUST_NO_CALLSINK") || fTopLoop == nullptr) {
        return;
    }
    std::vector<Statement> v(fTopLoop->fExecCode.begin(), fTopLoop->fExecCode.end());
    bool restart = true;
    int  guard   = 0;
    while (restart && guard++ < 32) {
        restart = false;
        for (size_t i = 0; i < v.size() && !restart; i++) {
            std::string lhs;
            bool        isDecl;
            if (!v[i].condition().empty() || !hasLibmCall(v[i].code()) ||
                !parseWriteTarget(v[i].code(), lhs, isDecl) || !isDecl) {
                continue;
            }
            std::vector<size_t>   group{i};
            std::set<std::string> defs{lhs}, reads;
            collectIdents(v[i].code(), reads);
            reads.erase(lhs);
            size_t stop = v.size();
            for (size_t j = i + 1; j < v.size(); j++) {
                std::set<std::string> mention;
                collectIdents(v[j].code(), mention);
                collectIdents(v[j].condition(), mention);
                std::string tlhs;
                bool        tdecl;
                bool        parsed = parseWriteTarget(v[j].code(), tlhs, tdecl);
                if (parsed && reads.count(tlhs)) {
                    stop = j;  // writes one of our inputs : hard barrier
                    break;
                }
                bool consumes = false;
                for (const auto& d : defs) {
                    if (mention.count(d)) {
                        consumes = true;
                        break;
                    }
                }
                if (!consumes) {
                    if (!parsed) {
                        stop = j;  // opaque statement : stay conservative
                        break;
                    }
                    continue;
                }
                // first consumer : a pure fresh temp joins the group,
                // anything else fixes the insertion point
                if (parsed && tdecl && v[j].condition().empty() && group.size() < 4) {
                    group.push_back(j);
                    defs.insert(tlhs);
                    mention.erase(tlhs);
                    for (const auto& m : mention) {
                        if (!defs.count(m)) {
                            reads.insert(m);
                        }
                    }
                    continue;
                }
                stop = j;
                break;
            }
            if (stop <= group.back() + 1) {
                continue;  // already adjacent to its consumer
            }
            std::vector<Statement> rebuilt;
            rebuilt.reserve(v.size());
            std::set<size_t> ingroup(group.begin(), group.end());
            for (size_t j = 0; j < v.size(); j++) {
                if (j == stop) {
                    for (size_t g : group) {
                        rebuilt.push_back(v[g]);
                    }
                }
                if (!ingroup.count(j)) {
                    rebuilt.push_back(v[j]);
                }
            }
            if (stop == v.size()) {
                for (size_t g : group) {
                    rebuilt.push_back(v[g]);
                }
            }
            v.swap(rebuilt);
            restart = true;
        }
    }
    fTopLoop->fExecCode.clear();
    fTopLoop->fExecCode.insert(fTopLoop->fExecCode.end(), v.begin(), v.end());
}

void Klass::printComputeMethodScalarBlock(int n, ostream& fout)
{
    if (!gGlobal->gLoopSplit) {
        sinkExpensiveCalls();
    }
    // Flat variant : a class with no per-block state machinery gains
    // nothing from the block chunking, and the &input[k][index] rebase
    // form costs the C compiler its aliasing analysis on the hot loop
    // (DNN : scalar ccmp check chains instead of vectorized ones, weight
    // constants rematerialized inside the loop -- 10% on the program).
    // Detection is a strict whitelist : no post-block code, and every
    // per-block line is an input/output pointer rebase. Stateful classes
    // (delay states, rings, IOTA) keep the chunked skeleton unchanged.
    bool flat = !gGlobal->gLoopSplit && fZone3Post.empty();
    if (flat) {
        for (const auto& s : fZone3Code) {
            bool comment = s.compare(0, 2, "//") == 0;
            if (!comment && s.find("= &input[") == string::npos &&
                s.find("= &output[") == string::npos) {
                flat = false;
                break;
            }
        }
    }
    if (flat) {
        tab(n + 1, fout);
        fout << subst("virtual void compute (int count, $0** input, $0** output) {", xfloat());
        printlines(n + 2, fZone1Code, fout);
        printlines(n + 2, fZone2Code, fout);
        printlines(n + 2, fZone2bCode, fout);
        tab(n + 2, fout);
        // index pinned to 0 : the zone-3 rebases fold to plain pointers
        fout << "const int index = 0; (void)index; // flat: stateless class";
        printlines(n + 2, fZone3Code, fout);
        printLoopGraphScalar(n + 2, fout);
        printlines(n + 2, fZone4Code, fout);
        tab(n + 1, fout);
        fout << "}";
        return;
    }

    tab(n + 1, fout);
    fout << subst("virtual void compute (int count, $0** input, $0** output) {", xfloat());
    printlines(n + 2, fZone1Code, fout);
    printlines(n + 2, fZone2Code, fout);
    printlines(n + 2, fZone2bCode, fout);

    tab(n + 2, fout);
    fout << "int fullcount = count;";
    tab(n + 2, fout);
    fout << "for (int index = 0; index < fullcount; index += " << gGlobal->gVecSize << ") {";
    tab(n + 3, fout);
    fout << "int count = faustmini(" << gGlobal->gVecSize << ", fullcount-index);";
    printlines(n + 3, fZone3Code, fout);
    printLoopGraphScalar(n + 3, fout);
    printlines(n + 3, fZone3Post, fout);
    tab(n + 2, fout);
    fout << "}";

    printlines(n + 2, fZone4Code, fout);
    tab(n + 1, fout);
    fout << "}";
}

/**
 * Uses loops of constant gVecSize boundary in order to provide the
 * C compiler with more optimisation opportunities. Improves performances
 * in general, but not always
 */
void Klass::printComputeMethodVectorFaster(int n, ostream& fout)
{
    // in vector mode we need to split loops in smaller pieces not larger
    // than gVecSize
    tab(n + 1, fout);
    fout << subst("virtual void compute (int count, $0** input, $0** output) {", xfloat());
    printlines(n + 2, fZone1Code, fout);
    printlines(n + 2, fZone2Code, fout);
    printlines(n + 2, fZone2bCode, fout);

    tab(n + 2, fout);
    fout << "int index;";
    tab(n + 2, fout);
    fout << "int fullcount = count;";

    tab(n + 2, fout);
    fout << "for (index = 0; index <= fullcount - " << gGlobal->gVecSize
         << "; index += " << gGlobal->gVecSize << ") {";
    tab(n + 3, fout);
    fout << "// compute by blocks of " << gGlobal->gVecSize << " samples";
    tab(n + 3, fout);
    fout << "const int count = " << gGlobal->gVecSize << ";";
    printlines(n + 3, fZone3Code, fout);
    printLoopGraphVector(n + 3, fout);
    tab(n + 2, fout);
    fout << "}";

    tab(n + 2, fout);
    fout << "if (index < fullcount) {";
    tab(n + 3, fout);
    fout << "// compute the remaining samples if any";
    tab(n + 3, fout);
    fout << "int count = fullcount-index;";
    printlines(n + 3, fZone3Code, fout);
    printLoopGraphVector(n + 3, fout);
    tab(n + 2, fout);
    fout << "}";

    printlines(n + 2, fZone4Code, fout);
    tab(n + 1, fout);
    fout << "}";
}

/**
 * Simple loop layout, generally less efficient than printComputeMethodVectorFaster
 */
void Klass::printComputeMethodVectorSimple(int n, ostream& fout)
{
    // in vector mode we need to split loops in smaller pieces not larger
    // than gVecSize
    tab(n + 1, fout);
    fout << subst("virtual void compute (int count, $0** input, $0** output) {", xfloat());
    printlines(n + 2, fZone1Code, fout);
    printlines(n + 2, fZone2Code, fout);
    printlines(n + 2, fZone2bCode, fout);

    tab(n + 2, fout);
    fout << "int fullcount = count;";
    tab(n + 2, fout);
    fout << "for (int index = 0; index < fullcount; index += " << gGlobal->gVecSize << ") {";
    tab(n + 3, fout);
    fout << "int count = faustmini(" << gGlobal->gVecSize << ", fullcount-index);";
    printlines(n + 3, fZone3Code, fout);
    printLoopGraphVector(n + 3, fout);
    tab(n + 2, fout);
    fout << "}";

    printlines(n + 2, fZone4Code, fout);
    tab(n + 1, fout);
    fout << "}";
}

/*
void Klass::printComputeMethodVectorFix0 (int n, ostream& fout)
{
    // in vector mode we need to split loops in smaller pieces not larger
    // than gVecSize
    tab(n+1,fout); fout << "virtual void compute (int fullcount, float** input, float** output) {";
        printlines(n+2, fZone1Code, fout);
        printlines(n+2, fZone2Code, fout);
        printlines(n+2, fZone2bCode, fout);
        tab(n+2,fout); fout << "for (int index = 0; index < fullcount; index += " << gVecSize << ")
{"; tab(n+3,fout); fout << "if (fullcount >= index + " << gVecSize << ") {"; tab(n+4,fout); fout <<
"// compute by blocks of " << gVecSize << " samples"; tab(n+4,fout); fout << "const int count = " <<
gVecSize << ";"; // temporaire printlines(n+4, fZone3Code, fout); printLoopGraph (n+4,fout);
            tab(n+3,fout); fout << "} else if (fullcount > index) {";
                //tab(n+3,fout); fout << "int count = min ("<< gVecSize << ", fullcount-index);";
                tab(n+4,fout); fout << "// compute the remaining samples";
                tab(n+4,fout); fout << "int count = fullcount-index;" ;
                printlines(n+4, fZone3Code, fout);
                printLoopGraph (n+4,fout);
            tab(n+3,fout); fout << "}";
        tab(n+2,fout); fout << "}";
    tab(n+1,fout); fout << "}";
}

void Klass::printComputeMethodVectorFix1 (int n, ostream& fout)
{
    // in vector mode we need to split loops in smaller pieces not larger
    // than gVecSize
    tab(n+1,fout); fout << "virtual void compute (int fullcount, float** input, float** output) {";
        printlines(n+2, fZone1Code, fout);
        printlines(n+2, fZone2Code, fout);
        printlines(n+2, fZone2bCode, fout);

        tab(n+2,fout); fout << "int \tblock;";
        tab(n+2,fout); fout << "for (block = 0; block < fullcount/" << gVecSize << "; block++) {";
            tab(n+3,fout); fout << "// compute by blocks of " << gVecSize << " samples";
            tab(n+3,fout); fout << "const int index = block*" << gVecSize << ";";
            tab(n+3,fout); fout << "const int count = " << gVecSize << ";"; // temporaire
            printlines(n+3, fZone3Code, fout);
            printLoopGraph (n+3,fout);
        tab(n+2,fout); fout << "}";

        tab(n+2,fout); fout << "if (fullcount%" << gVecSize << " != 0) {";
            //tab(n+3,fout); fout << "int count = min ("<< gVecSize << ", fullcount-index);";
            tab(n+3,fout); fout << "// compute the remaining samples";
            tab(n+3,fout); fout << "const int index = block*" << gVecSize << ";";
            tab(n+3,fout); fout << "int count = fullcount%" << gVecSize << ";" ;
            printlines(n+3, fZone3Code, fout);
            printLoopGraph (n+3,fout);
        tab(n+2,fout); fout << "}";
    tab(n+1,fout); fout << "}";
}*/

void Klass::printComputeMethodOpenMP(int n, ostream& fout)
{
    // in openMP mode we need to split loops in smaller pieces not larger
    // than gVecSize and add OpenMP pragmas
    tab(n + 1, fout);
    fout << subst("virtual void compute (int count, $0** input, $0** output) {", xfloat());
    printlines(n + 2, fZone1Code, fout);
    printlines(n + 2, fZone2Code, fout);
    tab(n + 2, fout);
    fout << "int fullcount = count;";
    tab(n + 2, fout);
    fout << "#pragma omp parallel";
    printdecllist(n + 3, "firstprivate", fFirstPrivateDecl, fout);

    tab(n + 2, fout);
    fout << "{";
    if (!fZone2bCode.empty()) {
        tab(n + 3, fout);
        fout << "#pragma omp single";
        tab(n + 3, fout);
        fout << "{";
        printlines(n + 4, fZone2bCode, fout);
        tab(n + 3, fout);
        fout << "}";
    }

    tab(n + 3, fout);
    fout << "for (int index = 0; index < fullcount; index += " << gGlobal->gVecSize << ") {";
    tab(n + 4, fout);
    fout << "int count = min (" << gGlobal->gVecSize << ", fullcount-index);";

    printlines(n + 4, fZone3Code, fout);
    printLoopGraphOpenMP(n + 4, fout);

    tab(n + 3, fout);
    fout << "}";

    tab(n + 2, fout);
    fout << "}";

    printlines(n + 2, fZone4Code, fout);
    tab(n + 1, fout);
    fout << "}";
}

/*
void Klass::printComputeMethodScheduler(int n, ostream& fout)
{
    tab(n+1,fout); fout << subst("virtual void compute (int fullcount, $0** input, $0** output) {",
xfloat()); printlines(n+2, fZone1Code, fout); printlines(n+2, fZone2Code, fout);

        // Init input and output
        tab(n+2,fout); fout << "// Init input and output";
        printlines(n+2, fZone3aCode, fout);
        printlines(n+2, fZone3bCode, fout);

        tab(n+2,fout); fout << "// Init graph state";
        tab(n+2,fout); fout << "initState(fTasksList);";
        tab(n+2,fout); fout << "bool is_finished = false;";
        tab(n+2,fout); fout << "unsigned int index_in = 0;";
        tab(n+2,fout); fout << "unsigned int index_out = 0;";
        tab(n+2,fout); fout << "int count = min ("<< gVecSize << ", fullcount);";

        tab(n+2,fout); fout << "InitSchedulingMap();";
        tab(n+2,fout); fout << "#pragma omp parallel";
        printdecllist(n+3, "firstprivate", fFirstPrivateDecl, fout);

        tab(n+2,fout); fout << "{";
            tab(n+3,fout); fout << "while (!is_finished) {";
                tab(n+4,fout); fout << "Task* task = searchTaskToAcquire(fTasksList);";
                tab(n+4,fout); fout << "if (task != NULL) {";
                    tab(n+5,fout); fout << "bool last_cycle_for_thread = false;";
                    tab(n+5,fout); fout << "do {";
                        tab(n+6,fout); fout << "AddTaskToScheduling(task);";
                        tab(n+6,fout); fout << "switch (task->fNum) {";

                            // DSP tasks
                            printLoopGraph (n+7,fout);

                            // Input task
                            tab(n+7, fout); fout << "case " << gTaskCount++ << ": { ";
                            printlines(n+8, fZone6Code, fout);
                            tab(n+8, fout); fout << "index_in += count;";
                            tab(n+8, fout); fout << "last_cycle_for_thread = (index_in >
fullcount);"; tab(n+8, fout); fout << "break;"; tab(n+7, fout); fout << "} ";

                            // Output task
                            tab(n+7, fout); fout << "case " << gTaskCount++ << ": { ";
                            printlines(n+8, fZone7Code, fout);
                            tab(n+8, fout); fout << "index_out += count;";
                            tab(n+8, fout); fout << "last_cycle_for_thread = (index_out >
fullcount);"; tab(n+8, fout); fout << "break;"; tab(n+7, fout); fout << "} ";

                            // End task
                            tab(n+7, fout); fout << "case " << gTaskCount++ << ": { ";
                            tab(n+8, fout); fout << "is_finished = ((index_in >= fullcount) &&
(index_out >= fullcount));"; tab(n+8, fout); fout << "break;"; tab(n+7, fout); fout << "} ";

                        tab(n+6,fout); fout << "}";
                        tab(n+6,fout); fout << "if (last_cycle_for_thread) break;";

                    tab(n+5,fout); fout << "} while ((task = task->concludeAndTryToAcquireNext()) !=
NULL);"; tab(n+4,fout); fout << "}"; tab(n+3,fout); fout << "}"; tab(n+2,fout); fout << "}";
        tab(n+2,fout); fout << "PrintSchedulingMap();";
    tab(n+1,fout); fout << "}";
}
*/

void Klass::printComputeMethodScheduler(int n, ostream& fout)
{
    tab(n + 1, fout);
    fout << "void display() {";
    tab(n + 2, fout);
    fout << "fGraph.Display();";
    tab(n + 1, fout);
    fout << "}";

    tab(n + 1, fout);
    fout << subst("virtual void compute (int count, $0** input, $0** output) {", xfloat());

    tab(n + 2, fout);
    fout << "GetRealTime();";

    tab(n + 2, fout);
    fout << "this->input = input;";
    tab(n + 2, fout);
    fout << "this->output = output;";

    tab(n + 2, fout);
    fout << "StartMeasure();";

    tab(n + 2, fout);
    fout << "int fullcount = count;";

    tab(n + 2, fout);
    fout << "for (fIndex = 0; fIndex < fullcount; fIndex += " << gGlobal->gVecSize << ") {";

    tab(n + 3, fout);
    fout << "fCount = min (" << gGlobal->gVecSize << ", fullcount-fIndex);";
    tab(n + 3, fout);
    fout << "TaskQueue::Init();";
    printlines(n + 3, fZone2cCode, fout);

    tab(n + 3, fout);
    fout << "fIsFinished = false;";
    tab(n + 3, fout);
    fout << "fThreadPool->SignalAll(fDynamicNumThreads - 1, this);";
    tab(n + 3, fout);
    fout << "computeThread(0);";
    tab(n + 3, fout);
    fout << "while (!fThreadPool->IsFinished()) {}";

    tab(n + 2, fout);
    fout << "}";

    tab(n + 2, fout);
    fout << "StopMeasure(fStaticNumThreads, fDynamicNumThreads);";

    tab(n + 1, fout);
    fout << "}";

    tab(n + 1, fout);
    fout << "void computeThread(int cur_thread) {";

    tab(n + 2, fout);
    fout << "int count = fCount;";

    printlines(n + 2, fZone1Code, fout);
    printlines(n + 2, fZone2Code, fout);

    tab(n + 2, fout);
    fout << "// Init graph state";

    tab(n + 2, fout);
    fout << "{";
    tab(n + 3, fout);
    fout << "TaskQueue taskqueue(cur_thread);";
    tab(n + 3, fout);
    fout << "int tasknum = -1;";

    // Init input and output
    tab(n + 3, fout);
    fout << "// Init input and output";
    printlines(n + 3, fZone3Code, fout);

    tab(n + 3, fout);
    fout << "while (!fIsFinished) {";
    tab(n + 4, fout);
    fout << "switch (tasknum) {";

    // Work stealing task
    tab(n + 5, fout);
    fout << "case WORK_STEALING_INDEX: { ";
    tab(n + 6, fout);
    fout << "tasknum = TaskQueue::GetNextTask(cur_thread, fDynamicNumThreads);";
    tab(n + 6, fout);
    fout << "break;";
    tab(n + 5, fout);
    fout << "} ";

    // End task
    tab(n + 5, fout);
    fout << "case LAST_TASK_INDEX: { ";
    tab(n + 6, fout);
    fout << "fIsFinished = true;";
    tab(n + 6, fout);
    fout << "break;";
    tab(n + 5, fout);
    fout << "} ";

    gTaskCount = START_TASK_INDEX;

    // DSP tasks
    printLoopGraphScheduler(n + 5, fout);

    tab(n + 4, fout);
    fout << "}";
    tab(n + 3, fout);
    fout << "}";
    tab(n + 2, fout);
    fout << "}";
    tab(n + 1, fout);
    fout << "}";
}

/**
 * Print an auxillary C++ class corresponding to an integer init signal
 */
void SigIntGenKlass::println(int n, ostream& fout)
{
    tab(n, fout);
    fout << "class " << fKlassName << " {";

    tab(n, fout);
    fout << "  private:";
    tab(n + 1, fout);
    fout << "int fSampleRate;";

    for (const auto& k : fSubClassList) {
        k->println(n + 1, fout);
    }

    printlines(n + 1, fDeclCode, fout);

    tab(n, fout);
    fout << "  public:";

    tab(n + 1, fout);
    fout << "int getNumInputs() { "
         << "return " << fNumInputs << "; }";
    tab(n + 1, fout);
    fout << "int getNumOutputs() { "
         << "return " << fNumOutputs << "; }";

    tab(n + 1, fout);
    fout << "void init(int sample_rate) {";
    tab(n + 2, fout);
    fout << "fSampleRate = sample_rate;";
    printlines(n + 2, fInitCode, fout);
    printlines(n + 2, fClearCode, fout);
    tab(n + 1, fout);
    fout << "}";

    tab(n + 1, fout);
    fout << "void fill(int count, int output[]) {";
    printlines(n + 2, fZone1Code, fout);
    printlines(n + 2, fZone2Code, fout);
    printlines(n + 2, fZone2bCode, fout);

    tab(n + 2, fout);
    fout << "int fullcount = count;";
    tab(n + 2, fout);
    fout << "for (int index = 0; index < fullcount; index += " << gGlobal->gVecSize << ") {";
    tab(n + 3, fout);
    fout << "int count = faustmini(" << gGlobal->gVecSize << ", fullcount-index);";
    printlines(n + 3, fZone3Code, fout);
    printLoopGraphInternal(n + 3, fout);
    printlines(n + 3, fZone3Post, fout);
    tab(n + 3, fout);
    fout << "output += " << gGlobal->gVecSize << ";";

    tab(n + 2, fout);
    fout << "}";

    printlines(n + 2, fZone4Code, fout);
    tab(n + 1, fout);
    fout << "}";

    tab(n, fout);
    fout << "};\n" << endl;
}

/**
 * Print an auxillary C++ class corresponding to an float init signal
 */
void SigFloatGenKlass::println(int n, ostream& fout)
{
    tab(n, fout);
    fout << "class " << fKlassName << " {";

    tab(n, fout);
    fout << "  private:";
    tab(n + 1, fout);
    fout << "int fSampleRate;";

    for (const auto& k : fSubClassList) {
        k->println(n + 1, fout);
    }

    printlines(n + 1, fDeclCode, fout);

    tab(n, fout);
    fout << "  public:";

    tab(n + 1, fout);
    fout << "int getNumInputs() { "
         << "return " << fNumInputs << "; }";
    tab(n + 1, fout);
    fout << "int getNumOutputs() { "
         << "return " << fNumOutputs << "; }";

    tab(n + 1, fout);
    fout << "void init(int sample_rate) {";
    tab(n + 2, fout);
    fout << "fSampleRate = sample_rate;";
    printlines(n + 2, fInitCode, fout);
    printlines(n + 2, fClearCode, fout);
    tab(n + 1, fout);
    fout << "}";

    tab(n + 1, fout);
    fout << subst("void fill(int count, $0 output[]) {", ifloat());
    printlines(n + 2, fZone1Code, fout);
    printlines(n + 2, fZone2Code, fout);
    printlines(n + 2, fZone2bCode, fout);

    tab(n + 2, fout);
    fout << "int fullcount = count;";
    tab(n + 2, fout);
    fout << "for (int index = 0; index < fullcount; index += " << gGlobal->gVecSize << ") {";
    tab(n + 3, fout);
    fout << "int count = faustmini(" << gGlobal->gVecSize << ", fullcount-index);";
    printlines(n + 3, fZone3Code, fout);
    printLoopGraphInternal(n + 3, fout);
    printlines(n + 3, fZone3Post, fout);
    tab(n + 3, fout);
    fout << "output += " << gGlobal->gVecSize << ";";

    tab(n + 2, fout);
    fout << "}";

    printlines(n + 2, fZone4Code, fout);
    tab(n + 1, fout);
    fout << "}";

    tab(n, fout);
    fout << "};\n" << endl;
}

static void merge(set<string>& dst, set<string>& src)
{
    for (const auto& i : src) {
        dst.insert(i);
    }
}

void Klass::collectIncludeFile(set<string>& S)
{
    for (const auto& k : fSubClassList) {
        k->collectIncludeFile(S);
    }
    merge(S, fIncludeFileSet);
}

void Klass::collectLibrary(set<string>& S)
{
    for (const auto& k : fSubClassList) {
        k->collectLibrary(S);
    }
    merge(S, fLibrarySet);
}

// every reference to vname in code must be exactly vname[0] or vname[1] on a
// word boundary ; counts them, or returns false on any other access form
static bool scanDelayRefs(const std::string& code, const std::string& vname, int& n0, int& n1)
{
    size_t p = 0;
    while ((p = code.find(vname, p)) != std::string::npos) {
        size_t q         = p + vname.size();
        bool   wordStart = (p == 0) || (!isalnum((unsigned char)code[p - 1]) && code[p - 1] != '_');
        bool   longerId  = (q < code.size()) && (isalnum((unsigned char)code[q]) || code[q] == '_');
        if (wordStart && !longerId) {
            if (code.compare(q, 3, "[0]") == 0) {
                n0++;
            } else if (code.compare(q, 3, "[1]") == 0) {
                n1++;
            } else {
                return false;
            }
        }
        p = q;
    }
    return true;
}

static void replaceAll(std::string& s, const std::string& from, const std::string& to)
{
    size_t p = 0;
    while ((p = s.find(from, p)) != std::string::npos) {
        s.replace(p, from.size(), to);
        p += to.size();
    }
}

bool Klass::scalarizeSingleDelay(const std::string& vname)
{
    // the structural pieces exactly as generateDelayLine wrote them
    const std::string declTail = vname + "[2];";
    const std::string loadLine = vname + "[1] = " + vname + "State;";
    const std::string saveLine = vname + "State = " + vname + "[1];";
    const std::string rotLine  = vname + "[1] = " + vname + "[0];";
    const std::string writePre = vname + "[0] = ";

    // ---- verification phase : nothing is touched unless EVERYTHING holds
    auto zone2It = fZone2Code.end();
    for (auto it = fZone2Code.begin(); it != fZone2Code.end(); ++it) {
        if (it->size() >= declTail.size() &&
            it->compare(it->size() - declTail.size(), declTail.size(), declTail) == 0) {
            zone2It = it;
            break;
        }
    }
    auto zone3It = std::find(fZone3Code.begin(), fZone3Code.end(), loadLine);
    auto z3pIt   = std::find(fZone3Post.begin(), fZone3Post.end(), saveLine);
    if (zone2It == fZone2Code.end() || zone3It == fZone3Code.end() || z3pIt == fZone3Post.end()) {
        return false;
    }
    auto rotIt = fTopLoop->fPostCode.end();
    for (auto it = fTopLoop->fPostCode.begin(); it != fTopLoop->fPostCode.end(); ++it) {
        int n0 = 0, n1 = 0;
        if (!scanDelayRefs(it->code(), vname, n0, n1)) {
            return false;
        }
        if (it->code() == rotLine) {
            rotIt = it;
        } else if (n0 || n1) {
            return false;  // a foreign post statement touches the vector
        }
    }
    if (rotIt == fTopLoop->fPostCode.end()) {
        return false;
    }
    for (auto& st : fTopLoop->fPreCode) {
        int n0 = 0, n1 = 0;
        if (!scanDelayRefs(st.code(), vname, n0, n1) || n0 || n1) {
            return false;  // pre-code must not touch the vector
        }
    }
    // the loop order : every [1] read at or before the write, [0] only after
    int idx = 0, writeIdx = -1, lastR1 = -1, firstR0 = -1;
    for (auto& st : fTopLoop->fExecCode) {
        int n0 = 0, n1 = 0;
        if (!scanDelayRefs(st.code(), vname, n0, n1)) {
            return false;
        }
        bool isWrite = st.code().compare(0, writePre.size(), writePre) == 0;
        if (isWrite) {
            if (writeIdx >= 0 || !st.condition().empty()) {
                return false;  // two writes, or a conditional one
            }
            writeIdx = idx;
        } else if ((n0 || n1) && !st.condition().empty()) {
            return false;  // conditional reader : stay conservative
        }
        if (n1 && !isWrite) {
            lastR1 = idx;
        }
        if (n0 && !isWrite && firstR0 < 0) {
            firstR0 = idx;
        }
        idx++;
    }
    if (writeIdx < 0 || lastR1 > writeIdx || (firstR0 >= 0 && firstR0 < writeIdx)) {
        return false;
    }

    // ---- commit : the vector degrades to a scalar, the rotation dies
    replaceAll(*zone2It, declTail, vname + ";");
    *zone3It = vname + " = " + vname + "State;";
    *z3pIt   = vname + "State = " + vname + ";";
    fTopLoop->fPostCode.erase(rotIt);
    std::list<Statement> newExec;
    for (auto& st : fTopLoop->fExecCode) {
        std::string c = st.code();
        replaceAll(c, vname + "[0]", vname);
        replaceAll(c, vname + "[1]", vname);
        newExec.push_back(Statement(st.condition(), c));
    }
    fTopLoop->fExecCode.swap(newExec);
    return true;
}
