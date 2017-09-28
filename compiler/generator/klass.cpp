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
			- klass.cpp : class C++ a remplir (projet FAUST) -

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

#include "floats.hh"
#include "smartpointer.hh"
#include "klass.hh"
#include "uitree.hh"
#include "Text.hh"
#include "signals.hh"
#include "ppsig.hh"
#include "recursivness.hh"

static int gTaskCount = 0;

bool Klass::fNeedPowerDef = false;

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
    return fLoopProperty.get(sig, l);
}

/**
 * Open a non-recursive loop on top of the stack of open loops.
 * @param size the number of iterations of the loop
 */
void Klass::openLoop(const string& size)
{
    fTopLoop = new Loop(fTopLoop, size);
    //cerr << "\nOPEN SHARED LOOP(" << size << ") ----> " << fTopLoop << endl;
}

/**
 * Open a recursive loop on top of the stack of open loops.
 * @param recsymbol the recursive symbol defined in this loop
 * @param size the number of iterations of the loop
 */
void Klass::openLoop(Tree recsymbol, const string& size)
{
    fTopLoop = new Loop(recsymbol, fTopLoop, size);
    //cerr << "\nOPEN REC LOOP(" << *recsymbol << ", " << size << ") ----> " << fTopLoop << endl;
}

/**
 * Close the top loop and either keep it
 * or absorb it within its enclosing loop.
 */
void Klass::closeLoop(Tree sig)
{
    faustassert(fTopLoop);
    Loop* l = fTopLoop;
    fTopLoop = l->fEnclosingLoop;
    faustassert(fTopLoop);

    //l->println(4, cerr);
    //cerr << endl;

    Tree S = symlist(sig);
    //cerr << "CLOSE LOOP :" << l << " with symbols " << *S  << endl;
    if (l->isEmpty() || fTopLoop->hasRecDependencyIn(S)) {
        //cout << " will absorb" << endl;
        // empty or dependent loop -> absorbed by enclosing one
        //cerr << "absorbed by : " << fTopLoop << endl;
        fTopLoop->absorb(l);
        //delete l; HACK !!!
    } else {
        // cout << " will NOT absorb" << endl;
        // we have an independent loop
        setLoopProperty(sig,l);     // associate the signal
        fTopLoop->fBackwardLoopDependencies.insert(l);
        // we need to indicate that all recursive symbols defined
        // in this loop are defined in this loop
        for (Tree lsym=l->fRecSymbolSet; !isNil(lsym); lsym=tl(lsym)) {
            this->setLoopProperty(hd(lsym), l);
            //cerr << "loop " << l << " defines " << *hd(lsym) << endl;
        }
    }
    //cerr << "\n" << endl;
}

/**
 * Print a list of elements (e1, e2,...)
 */
void printdecllist(int n, const string& decl, list<string>& content, ostream& fout)
{
    if (!content.empty()) {
        list<string>::iterator s;
        fout << "\\";
        tab(n, fout); fout << decl;
        string sep = "(";
        for (s = content.begin(); s != content.end(); s++) {
            fout << sep << *s;
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

    if (gGlobal->gOpenMPSwitch) {
        fout << "#include <omp.h>" << "\n";
    }

    collectIncludeFile(S);
    for (f = S.begin(); f != S.end(); f++) 	{
        string inc = *f;
        // Only print non-empty include (inc is actually quoted)
        if (inc.size() > 2) { 
            fout << "#include " << *f << "\n";
        }
    }
}

/**
 * Print additional functions required by the generated code
 */
void Klass::printAdditionalCode(ostream& fout)
{
    if (fNeedPowerDef) {
        // Add faustpower definition to C++ code
        fout << "#ifndef FAUSTPOWER" << endl;
        fout << "#define FAUSTPOWER" << endl;
        fout << "#include <cmath>" << endl;
        
        fout << "template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } " << endl;
        fout << "template <> 	 inline int faustpower<0>(int x)            { return 1; }" << endl;
        fout << "template <> 	 inline int faustpower<1>(int x)            { return x; }" << endl;
        fout << "template <> 	 inline int faustpower<2>(int x)            { return x*x; }" << endl;
        
        if (gGlobal->gFloatSize == 1) {
            
            fout << "template <int N> inline float faustpower(float x)            { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } " << endl;
            fout << "template <> 	 inline float faustpower<0>(float x)          { return 1; }" << endl;
            fout << "template <> 	 inline float faustpower<1>(float x)          { return x; }" << endl;
            fout << "template <> 	 inline float faustpower<2>(float x)          { return x*x; }" << endl;
            
        } else if (gGlobal->gFloatSize == 2) {
        
            fout << "template <int N> inline double faustpower(double x)          { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } " << endl;
            fout << "template <> 	 inline double faustpower<0>(double x)        { return 1; }" << endl;
            fout << "template <> 	 inline double faustpower<1>(double x)        { return x; }" << endl;
            fout << "template <> 	 inline double faustpower<2>(double x)        { return x*x; }" << endl;
            
        } else if (gGlobal->gFloatSize == 3) {
            
            fout << "template <int N> inline long double faustpower(long double x){ return powl(x,N); }"  << endl;
            
        }
        fout << "#endif" << endl;

    }
}

/**
 * Print metadata declaration
 */
void Klass::printMetadata(int n, const MetaDataSet& S, ostream& fout)
{
    tab(n,fout); fout << "virtual void metadata(Meta* m) { ";
    
    // We do not want to accumulate metadata from all hierachical levels, so the upper level only is kept
    for (MetaDataSet::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
        if (i->first != tree("author")) {
            tab(n+1,fout); fout << "m->declare(\"" << *(i->first) << "\", " << **(i->second.begin()) << ");";
        } else {
            // But the "author" meta data is accumulated, the upper level becomes the main author and sub-levels become "contributor"
            for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); j++) {
                if (j == i->second.begin()) {
                     tab(n+1,fout); fout << "m->declare(\"" << *(i->first) << "\", " << **j << ");" ;
                } else {
                     tab(n+1,fout); fout << "m->declare(\"" << "contributor" << "\", " << **j << ");";
                }
            }
        }
    }

    tab(n,fout); fout << "}" << endl;
}

inline bool isElement(const set<Loop*>& S, Loop* l)
{
	return S.find(l)!= S.end();
}

/**
 * Print a loop graph deep first
 */
void Klass::printLoopDeepFirst(int n, ostream& fout, Loop* l, set<Loop*>& visited)
{
	// avoid printing already printed loops
	if (isElement(visited, l)) return;

	// remember we have printed this loop
	visited.insert(l);

	// print the dependencies loops (that need to be computed before this one)
	for (lset::const_iterator p =l->fBackwardLoopDependencies.begin(); p!=l->fBackwardLoopDependencies.end(); p++) {
        printLoopDeepFirst(n, fout, *p, visited);
    }
    // the print the loop itself
    tab(n, fout);
    tab(n, fout); fout << "// LOOP " << l << ", ORDER " << l->fOrder << endl;
    l->println(n+1, fout);
}

/**
 * Compute how many time each loop is used in a DAG
 */
static void computeUseCount(Loop* l)
{
	l->fUseCount++;
	if (l->fUseCount == 1) {
		for (lset::iterator p =l->fBackwardLoopDependencies.begin(); p!=l->fBackwardLoopDependencies.end(); p++) {
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
        if (n==0) {
            return;
        } else if (n==1) {
            Loop* f = *(l->fBackwardLoopDependencies.begin());
            if (f->fUseCount ==  1) {
                l->concat(f);
                groupSeqLoops(l, visited);
            } else {
                groupSeqLoops(f, visited);
            }
            return;
        } else if (n > 1) {
            for (lset::iterator p =l->fBackwardLoopDependencies.begin(); p!=l->fBackwardLoopDependencies.end(); p++) {
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
    for (int l=(int)G.size()-1; l>=0; l--) {
        for (lset::const_iterator p =G[l].begin(); p!=G[l].end(); p++) {
            for (lset::const_iterator p1 = (*p)->fBackwardLoopDependencies.begin(); p1!=(*p)->fBackwardLoopDependencies.end(); p1++) {
                (*p1)->fForwardLoopDependencies.insert((*p));
            }
            (*p)->fIndex = index_task;
            index_task++;
        }
    }

    // Compute ready tasks list
    vector<int> task_num;
    for (int l=(int)G.size()-1; l>=0; l--) {
        lset::const_iterator next;
        for (lset::const_iterator p =G[l].begin(); p!=G[l].end(); p++) {
            if ((*p)->fBackwardLoopDependencies.size() == 0) {
                task_num.push_back((*p)->fIndex);
            }
        }
    }

    if (task_num.size() < START_TASK_MAX) {

        // Push ready tasks thread 0, execute one task directly

        addZone3("if (cur_thread == 0) {");

        Loop* keep = NULL;
        for (int l=(int)G.size()-1; l>=0; l--) {
            lset::const_iterator next;
            for (lset::const_iterator p =G[l].begin(); p!=G[l].end(); p++) {
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
        for(size_t i = 0; i < task_num.size(); i++) {
            buf << task_num[i];
            if (i != (task_num.size() - 1))
                buf << ",";
        }
        buf << "};";

        addZone3(buf.str());
        addZone3("taskqueue.InitTaskList(task_list_size, task_list, fDynamicNumThreads, cur_thread, tasknum);");
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
    for (int l=(int)G.size()-1; l>=0; l--) {
        for (lset::const_iterator p =G[l].begin(); p!=G[l].end(); p++) {
            if ((*p)->fBackwardLoopDependencies.size() > 1)  { // Only initialize taks with more than 1 input, since taks with one input are "directly" activated.
                addZone2c(subst("fGraph.InitTask($0,$1);", T(START_TASK_INDEX + gTaskCount++), T((int)(*p)->fBackwardLoopDependencies.size())));
            } else {
                gTaskCount++;
            }
        }
    }

    addInitCode("fStaticNumThreads = get_max_cpu();");
    addInitCode("fDynamicNumThreads = getenv(\"OMP_NUM_THREADS\") ? atoi(getenv(\"OMP_NUM_THREADS\")) : fStaticNumThreads;");
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
    for (int l=(int)G.size()-1; l>=0; l--) {
        if (gGlobal->gVectorSwitch) { tab(n, fout); fout << "// SECTION : " << G.size() - l; }
        for (lset::const_iterator p =G[l].begin(); p!=G[l].end(); p++) {
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
    for (int l=(int)G.size()-1; l>=0; l--) {
        tab(n, fout); fout << "// SECTION : " << G.size() - l;
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
    for (int l=(int)G.size()-1; l>0; l--) {
        tab(n, fout); fout << "// SECTION : " << G.size() - l;
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

    int lnum = 0;       // used for loop numbers
    // for each level of the graph
    for (int l=(int)G.size()-1; l>=0; l--) {
        // for each task in the level
        for (lset::const_iterator t =G[l].begin(); t!=G[l].end(); t++) {
            // print task label "Lxxx : 0xffffff"
            fout << '\t' << 'L'<<(*t)<<"[label=<<font face=\"verdana,bold\">L"<<lnum++<<"</font> : "<<(*t)<<">];"<<endl;
            // for each source of the task
            for (lset::const_iterator src = (*t)->fBackwardLoopDependencies.begin(); src!=(*t)->fBackwardLoopDependencies.end(); src++) {
                // print the connection Lxxx -> Lyyy;
                fout << '\t' << 'L'<<(*src)<<"->"<<'L'<<(*t)<<';'<<endl;
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
    for (int l=(int)G.size()-1; l>=0; l--) {
        if (gGlobal->gVectorSwitch) { tab(n, fout); fout << "// SECTION : " << G.size() - l; }
        for (lset::const_iterator p =G[l].begin(); p!=G[l].end(); p++) {
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
    for (lset::const_iterator p =L.begin(); p!=L.end(); p++) {
        if ((*p)->fIsRecursive) return false;
    }
    return true;
}

/**
 * Print the 'level' of the loop graph as a set of
 * parallel loops
 */
void Klass::printLoopLevelOpenMP(int n, int lnum, const lset& L, ostream& fout)
{
    if (nonRecursiveLevel(L) && L.size()==1) {
        for (lset::const_iterator p =L.begin(); p!=L.end(); p++) {
            if ((*p)->isEmpty() == false) {
                if (gGlobal->gOpenMPLoop) {
                    (*p)->printParLoopln(n, fout);
                } else {
                    tab(n, fout); fout << "#pragma omp single ";
                    tab(n, fout); fout << "{ ";
                    (*p)->println(n+1, fout);
                    tab(n, fout); fout << "} ";
                }
            }
        }

    } else if (L.size() > 1) {
        tab(n, fout); fout << "#pragma omp sections ";
        tab(n, fout); fout << "{ ";
        for (lset::const_iterator p =L.begin(); p!=L.end(); p++) {
            tab(n+1, fout); fout << "#pragma omp section ";
            tab(n+1, fout); fout << "{";
            (*p)->println(n+2, fout);
            tab(n+1, fout); fout << "} ";
        }
        tab(n, fout); fout << "} ";
    } else if (L.size() == 1 && !(*L.begin())->isEmpty()) {
        tab(n, fout); fout << "#pragma omp single ";
        tab(n, fout); fout << "{ ";
            for (lset::const_iterator p =L.begin(); p!=L.end(); p++) {
                (*p)->println(n+1, fout);
            }
        tab(n, fout); fout << "} ";
    }
}

/**
 * Print the 'level' of the loop graph as a set of
 * parallel loops
 */
void Klass::printLastLoopLevelScheduler(int n, int lnum, const lset& L, ostream& fout)
{
    if (nonRecursiveLevel(L) && L.size() == 1 && !(*L.begin())->isEmpty()) {

        lset::const_iterator p =L.begin();
        tab(n, fout); fout << "case " << gTaskCount++ << ": { ";
        (*p)->println(n+1, fout);
        tab(n+1, fout); fout << "tasknum = LAST_TASK_INDEX;";
        tab(n+1, fout); fout << "break;";
        tab(n, fout); fout << "} ";

    } else if (L.size() > 1) {

        for (lset::const_iterator p =L.begin(); p!=L.end(); p++) {
            tab(n, fout); fout << "case " << gTaskCount++ << ": { ";
            (*p)->println(n+1, fout);
            tab(n+1, fout); fout << "fGraph.ActivateOneOutputTask(taskqueue, LAST_TASK_INDEX, tasknum);";
            tab(n+1, fout); fout << "break;";
            tab(n, fout); fout << "} ";
        }

    } else if (L.size() == 1 && !(*L.begin())->isEmpty()) {

        lset::const_iterator p =L.begin();
        tab(n, fout); fout << "case " << gTaskCount++ << ": { ";
        (*p)->println(n+1, fout);
        tab(n+1, fout); fout << "tasknum = LAST_TASK_INDEX;";
        tab(n+1, fout); fout << "break;";
        tab(n, fout); fout << "} ";

    }
}

void Klass::printOneLoopScheduler(lset::const_iterator p, int n, ostream& fout)
{
    tab(n, fout); fout << "case " << gTaskCount++ << ": { ";
    (*p)->println(n+1, fout);

    // One output only
    if ((*p)->fForwardLoopDependencies.size() == 1) {

        lset::const_iterator p1 = (*p)->fForwardLoopDependencies.begin();
        if ((*p1)->fBackwardLoopDependencies.size () == 1) {
            tab(n+1, fout); fout << subst("tasknum = $0;", T((*p1)->fIndex));
        } else {
            tab(n+1, fout); fout << subst("fGraph.ActivateOneOutputTask(taskqueue, $0, tasknum);", T((*p1)->fIndex));
        }

    } else {

        Loop* keep = NULL;
        // Find one output with only one backward dependencies
        for (lset::const_iterator p1 = (*p)->fForwardLoopDependencies.begin(); p1!=(*p)->fForwardLoopDependencies.end(); p1++) {
            if ((*p1)->fBackwardLoopDependencies.size () == 1) {
                keep = *p1;
                break;
            }
        }

        if (keep == NULL) {
            tab(n+1, fout); fout << "tasknum = WORK_STEALING_INDEX;";
        }

        for (lset::const_iterator p1 = (*p)->fForwardLoopDependencies.begin(); p1!=(*p)->fForwardLoopDependencies.end(); p1++) {
            if ((*p1)->fBackwardLoopDependencies.size () == 1) {  // Task is the only input
                if (*p1 != keep) {
                    tab(n+1, fout); fout << subst("taskqueue.PushHead($0);", T((*p1)->fIndex));
                }
            } else {
                if (keep == NULL) {
                    tab(n+1, fout); fout << subst("fGraph.ActivateOutputTask(taskqueue, $0, tasknum);", T((*p1)->fIndex));
                } else {
                    tab(n+1, fout); fout << subst("fGraph.ActivateOutputTask(taskqueue, $0);", T((*p1)->fIndex));
                }
            }
        }

        if (keep != NULL) {
            tab(n+1, fout); fout << subst("tasknum = $0;", T(keep->fIndex)); // Last one
        } else {
            tab(n+1, fout); fout << "fGraph.GetReadyTask(taskqueue, tasknum);"; // Last one
        }
    }

    tab(n+1, fout); fout << "break;";
    tab(n, fout); fout << "} ";
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
	list<Klass* >::iterator k;

    tab(n,fout); fout << "#ifndef FAUSTCLASS " << endl;
    fout << "#define FAUSTCLASS "<< fKlassName << endl;
    fout << "#endif" << endl;

    if (gGlobal->gSchedulerSwitch) {
        tab(n,fout); fout << "class " << fKlassName << " : public " << fSuperKlassName << ", public Runnable {";
    } else {
        tab(n,fout); fout << "class " << fKlassName << " : public " << fSuperKlassName << " {";
    }

    if (gGlobal->gUIMacroSwitch) {
        tab(n,fout); fout << "  public:";
    } else {
	    tab(n,fout); fout << "  private:";
    }

    for (k = fSubClassList.begin(); k != fSubClassList.end(); k++) 	(*k)->println(n+1, fout);

    printlines(n+1, fDeclCode, fout);
    
    tab(n+1,fout); fout << "int fSamplingFreq;\n";

    tab(n,fout); fout << "  public:";
    
    if (gGlobal->gMemoryManager) {
        tab(n+1,fout); fout << "static dsp_memory_manager* fManager;" << endl;
    }

    printMetadata(n+1, gGlobal->gMetaDataSet, fout);

    if (gGlobal->gSchedulerSwitch) {
        tab(n+1,fout); fout << fKlassName << "() { "
                            << "fThreadPool = DSPThreadPool::Init(); }";
        
        tab(n+1,fout); fout << "virtual ~" << fKlassName << "() { "
                            << "DSPThreadPool::Destroy(); }";
    }
    
    tab(n+1,fout); fout << "virtual int getNumInputs() { "
                    << "return " << fNumInputs
                    << "; }";
    
    tab(n+1,fout); fout << "virtual int getNumOutputs() { "
                    << "return " << fNumOutputs
                    << "; }";

    tab(n+1,fout); fout << "static void classInit(int samplingFreq) {";
        printlines(n+2, fStaticInitCode, fout);
    tab(n+1,fout); fout << "}";
    
    if (gGlobal->gMemoryManager) {
        tab(n+1,fout); fout << "static void classDestroy() {";
            printlines(n+2, fStaticDestroyCode, fout);
        tab(n+1,fout); fout << "}";
    }

    tab(n+1,fout); fout << "virtual void instanceConstants(int samplingFreq) {";
        tab(n+2,fout); fout << "fSamplingFreq = samplingFreq;";
        printlines(n+2, fInitCode, fout);
    tab(n+1,fout); fout << "}";
    
    tab(n+1,fout); fout << "virtual void instanceResetUserInterface() {";
        printlines(n+2, fInitUICode, fout);
    tab(n+1,fout); fout << "}";
    
    tab(n+1,fout); fout << "virtual void instanceClear() {";
        printlines(n+2, fClearCode, fout);
    tab(n+1,fout); fout << "}";

    if (gGlobal->gMemoryManager) {
        tab(n+1,fout); fout << "virtual void init(int samplingFreq) {}";
    } else {
        tab(n+1,fout); fout << "virtual void init(int samplingFreq) {";
            tab(n+2,fout); fout << "classInit(samplingFreq);";
            tab(n+2,fout); fout << "instanceInit(samplingFreq);";
        tab(n+1,fout); fout << "}";
    }
    
    tab(n+1,fout); fout << "virtual void instanceInit(int samplingFreq) {";
        tab(n+2,fout); fout << "instanceConstants(samplingFreq);";
        tab(n+2,fout); fout << "instanceResetUserInterface();";
        tab(n+2,fout); fout << "instanceClear();";
    tab(n+1,fout); fout << "}";
    
    tab(n+1,fout); fout << "virtual "<< fKlassName <<"* clone() {";
        tab(n+2,fout); fout << "return new " << fKlassName << "();";
    tab(n+1,fout); fout << "}";
    
    tab(n+1,fout); fout << "virtual int getSampleRate() {";
        tab(n+2,fout); fout << "return fSamplingFreq;";
    tab(n+1,fout); fout << "}";

    tab(n+1,fout); fout << "virtual void buildUserInterface(UI* ui_interface) {";
        printlines(n+2, fUICode, fout);
    tab(n+1,fout); fout << "}";

    printComputeMethod(n, fout);

	tab(n,fout); fout << "};\n" << endl;

	printlines(n, fStaticFields, fout);
    
    if (gGlobal->gMemoryManager) {
        tab(n, fout); fout << "dsp_memory_manager* " << fKlassName <<"::fManager = 0;" << endl;
    }
    
	// generate user interface macros if needed
	if (gGlobal->gUIMacroSwitch) {
		tab(n, fout); fout << "#ifdef FAUST_UIMACROS";
            tab(n+1,fout); fout << "#define FAUST_INPUTS " << fNumInputs;
            tab(n+1,fout); fout << "#define FAUST_OUTPUTS " << fNumOutputs;
            tab(n+1,fout); fout << "#define FAUST_ACTIVES " << fNumActives;
            tab(n+1,fout); fout << "#define FAUST_PASSIVES " << fNumPassives;
			printlines(n+1, fUIMacro, fout);
		tab(n, fout); fout << "#endif";
	}

	fout << endl;
}

/**
 * Print Compute() method according to the various switch
 */
void Klass::printComputeMethod(int n, ostream& fout)
{
    if (gGlobal->gSchedulerSwitch) {
        printComputeMethodScheduler (n, fout);
    } else if (gGlobal->gOpenMPSwitch) {
        printComputeMethodOpenMP (n, fout);
    } else if (gGlobal->gVectorSwitch) {
        switch (gGlobal->gVectorLoopVariant) {
            case 0 : printComputeMethodVectorFaster(n, fout); break;
            case 1 : printComputeMethodVectorSimple(n, fout); break;
            default : cerr << "unknown loop variant " << gGlobal->gVectorLoopVariant << endl; exit(1);
        }
   } else {
        printComputeMethodScalar(n, fout);
    }
}

void Klass::printComputeMethodScalar(int n, ostream& fout)
{
    tab(n+1,fout); fout << subst("virtual void compute (int count, $0** input, $0** output) {", xfloat());
        tab(n+2,fout); fout << "//zone1";
        printlines(n+2, fZone1Code, fout);
        tab(n+2,fout); fout << "//zone2";
        printlines(n+2, fZone2Code, fout);
        tab(n+2,fout); fout << "//zone2b";
        printlines(n+2, fZone2bCode, fout);
        tab(n+2,fout); fout << "//zone3";
        printlines(n+2, fZone3Code, fout);
        tab(n+2,fout); fout << "//LoopGraphScalar";
        printLoopGraphScalar (n+2,fout);
        printlines(n+2, fZone4Code, fout);
    tab(n+1,fout); fout << "}";
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
    tab(n+1,fout); fout << subst("virtual void compute (int count, $0** input, $0** output) {", xfloat());
        printlines(n+2, fZone1Code, fout);
        printlines(n+2, fZone2Code, fout);
        printlines(n+2, fZone2bCode, fout);

        tab(n+2,fout); fout << "int index;";
		tab(n+2,fout); fout << "int fullcount = count;";
		
        tab(n+2,fout); fout << "for (index = 0; index <= fullcount - " << gGlobal->gVecSize << "; index += " << gGlobal->gVecSize << ") {";
            tab(n+3,fout); fout << "// compute by blocks of " << gGlobal->gVecSize << " samples";
            tab(n+3,fout); fout << "const int count = " << gGlobal->gVecSize << ";";
            printlines(n+3, fZone3Code, fout);
            printLoopGraphVector(n+3,fout);
        tab(n+2,fout); fout << "}";

        tab(n+2,fout); fout << "if (index < fullcount) {";
            tab(n+3,fout); fout << "// compute the remaining samples if any";
            tab(n+3,fout); fout << "int count = fullcount-index;";
            printlines(n+3, fZone3Code, fout);
             printLoopGraphVector(n+3,fout);
        tab(n+2,fout); fout << "}";

        printlines(n+2, fZone4Code, fout);
    tab(n+1,fout); fout << "}";
}

/**
 * Simple loop layout, generally less efficient than printComputeMethodVectorFaster
 */
void Klass::printComputeMethodVectorSimple(int n, ostream& fout)
{
    // in vector mode we need to split loops in smaller pieces not larger
    // than gVecSize
    tab(n+1,fout); fout << subst("virtual void compute (int count, $0** input, $0** output) {", xfloat());
        printlines(n+2, fZone1Code, fout);
        printlines(n+2, fZone2Code, fout);
        printlines(n+2, fZone2bCode, fout);
		
        tab(n+2,fout); fout << "int fullcount = count;";
		tab(n+2,fout); fout << "for (int index = 0; index < fullcount; index += " << gGlobal->gVecSize << ") {";
            tab(n+3,fout); fout << "int count = min("<< gGlobal->gVecSize << ", fullcount-index);";
            printlines(n+3, fZone3Code, fout);
            printLoopGraphVector(n+3,fout);
        tab(n+2,fout); fout << "}";

        printlines(n+2, fZone4Code, fout);
    tab(n+1,fout); fout << "}";
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
        tab(n+2,fout); fout << "for (int index = 0; index < fullcount; index += " << gVecSize << ") {";
            tab(n+3,fout); fout << "if (fullcount >= index + " << gVecSize << ") {";
                tab(n+4,fout); fout << "// compute by blocks of " << gVecSize << " samples";
                tab(n+4,fout); fout << "const int count = " << gVecSize << ";"; // temporaire
                printlines(n+4, fZone3Code, fout);
                printLoopGraph (n+4,fout);
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
    tab(n+1,fout); fout << subst("virtual void compute (int count, $0** input, $0** output) {", xfloat());
        printlines(n+2, fZone1Code, fout);
        printlines(n+2, fZone2Code, fout);
        tab(n+2,fout); fout << "int fullcount = count;";
        tab(n+2,fout); fout << "#pragma omp parallel";
        printdecllist(n+3, "firstprivate", fFirstPrivateDecl, fout);

        tab(n+2,fout); fout << "{";
            if (!fZone2bCode.empty()) {
                tab(n+3,fout); fout << "#pragma omp single";
                tab(n+3,fout); fout << "{";
                    printlines(n+4, fZone2bCode, fout);
                tab(n+3,fout); fout << "}";
            }

            tab(n+3,fout); fout << "for (int index = 0; index < fullcount; index += " << gGlobal->gVecSize << ") {";
            tab(n+4,fout); fout << "int count = min ("<< gGlobal->gVecSize << ", fullcount-index);";

            printlines(n+4, fZone3Code, fout);
            printLoopGraphOpenMP(n+4,fout);

            tab(n+3,fout); fout << "}";

        tab(n+2,fout); fout << "}";

        printlines(n+2, fZone4Code, fout);
    tab(n+1,fout); fout << "}";
}

/*
void Klass::printComputeMethodScheduler (int n, ostream& fout)
{
    tab(n+1,fout); fout << subst("virtual void compute (int fullcount, $0** input, $0** output) {", xfloat());
        printlines(n+2, fZone1Code, fout);
        printlines(n+2, fZone2Code, fout);

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
                            tab(n+8, fout); fout << "last_cycle_for_thread = (index_in > fullcount);";
                            tab(n+8, fout); fout << "break;";
                            tab(n+7, fout); fout << "} ";

                            // Output task
                            tab(n+7, fout); fout << "case " << gTaskCount++ << ": { ";
                            printlines(n+8, fZone7Code, fout);
                            tab(n+8, fout); fout << "index_out += count;";
                            tab(n+8, fout); fout << "last_cycle_for_thread = (index_out > fullcount);";
                            tab(n+8, fout); fout << "break;";
                            tab(n+7, fout); fout << "} ";

                            // End task
                            tab(n+7, fout); fout << "case " << gTaskCount++ << ": { ";
                            tab(n+8, fout); fout << "is_finished = ((index_in >= fullcount) && (index_out >= fullcount));";
                            tab(n+8, fout); fout << "break;";
                            tab(n+7, fout); fout << "} ";

                        tab(n+6,fout); fout << "}";
                        tab(n+6,fout); fout << "if (last_cycle_for_thread) break;";

                    tab(n+5,fout); fout << "} while ((task = task->concludeAndTryToAcquireNext()) != NULL);";
                tab(n+4,fout); fout << "}";
            tab(n+3,fout); fout << "}";
        tab(n+2,fout); fout << "}";
        tab(n+2,fout); fout << "PrintSchedulingMap();";
    tab(n+1,fout); fout << "}";
}
*/

void Klass::printComputeMethodScheduler (int n, ostream& fout)
{
    tab(n+1,fout); fout << "void display() {";
        tab(n+2,fout); fout << "fGraph.Display();";
    tab(n+1,fout); fout << "}";

    tab(n+1,fout); fout << subst("virtual void compute (int count, $0** input, $0** output) {", xfloat());

        tab(n+2,fout); fout << "GetRealTime();";

        tab(n+2,fout); fout << "this->input = input;";
        tab(n+2,fout); fout << "this->output = output;";

        tab(n+2,fout); fout << "StartMeasure();";
        
        tab(n+2,fout); fout << "int fullcount = count;";

        tab(n+2,fout); fout << "for (fIndex = 0; fIndex < fullcount; fIndex += " << gGlobal->gVecSize << ") {";

        tab(n+3,fout); fout << "fCount = min ("<< gGlobal->gVecSize << ", fullcount-fIndex);";
        tab(n+3,fout); fout << "TaskQueue::Init();";
        printlines(n+3, fZone2cCode, fout);

        tab(n+3,fout); fout << "fIsFinished = false;";
        tab(n+3,fout); fout << "fThreadPool->SignalAll(fDynamicNumThreads - 1, this);";
        tab(n+3,fout); fout << "computeThread(0);";
        tab(n+3,fout); fout << "while (!fThreadPool->IsFinished()) {}";

        tab(n+2,fout); fout << "}";

        tab(n+2,fout); fout << "StopMeasure(fStaticNumThreads, fDynamicNumThreads);";

    tab(n+1,fout); fout << "}";

    tab(n+1,fout); fout << "void computeThread(int cur_thread) {";
    
        tab(n+2,fout); fout << "int count = fCount;";
        
        printlines(n+2, fZone1Code, fout);
        printlines(n+2, fZone2Code, fout);

        tab(n+2,fout); fout << "// Init graph state";

        tab(n+2,fout); fout << "{";
            tab(n+3,fout); fout << "TaskQueue taskqueue(cur_thread);";
            tab(n+3,fout); fout << "int tasknum = -1;";
    
            // Init input and output
            tab(n+3,fout); fout << "// Init input and output";
            printlines(n+3, fZone3Code, fout);

            tab(n+3,fout); fout << "while (!fIsFinished) {";
                 tab(n+4,fout); fout << "switch (tasknum) {";

                    // Work stealing task
                    tab(n+5, fout); fout << "case WORK_STEALING_INDEX: { ";
                        tab(n+6, fout); fout << "tasknum = TaskQueue::GetNextTask(cur_thread, fDynamicNumThreads);";
                        tab(n+6, fout); fout << "break;";
                    tab(n+5, fout); fout << "} ";

                    // End task
                    tab(n+5, fout); fout << "case LAST_TASK_INDEX: { ";
                        tab(n+6, fout); fout << "fIsFinished = true;";
                        tab(n+6, fout); fout << "break;";
                    tab(n+5, fout); fout << "} ";

                    gTaskCount = START_TASK_INDEX;

                    // DSP tasks
                    printLoopGraphScheduler(n+5,fout);

                 tab(n+4,fout); fout << "}";
            tab(n+3,fout); fout << "}";
        tab(n+2,fout); fout << "}";
    tab(n+1,fout); fout << "}";
}

/**
 * Print an auxillary C++ class corresponding to an integer init signal
 */
void SigIntGenKlass::println(int n, ostream& fout)
{
	list<Klass* >::iterator k;

	tab(n,fout); fout << "class " << fKlassName << " {";

	tab(n,fout); fout << "  private:";
		tab(n+1,fout); fout << "int fSamplingFreq;";

		for (k = fSubClassList.begin(); k != fSubClassList.end(); k++) 	(*k)->println(n+1, fout);

		printlines(n+1, fDeclCode, fout);

	tab(n,fout); fout << "  public:";

		tab(n+1,fout); fout << "int getNumInputs() { "
						<< "return " << fNumInputs << "; }";
		tab(n+1,fout); fout << "int getNumOutputs() { "
						<< "return " << fNumOutputs << "; }";

		tab(n+1,fout); fout << "void init(int samplingFreq) {";
			tab(n+2,fout); fout << "fSamplingFreq = samplingFreq;";
            printlines(n+2, fInitCode, fout);
            printlines(n+2, fClearCode, fout);
		tab(n+1,fout); fout << "}";

		tab(n+1,fout); fout << "void fill (int count, int output[]) {";
            printlines(n+2, fZone1Code, fout);
            printlines(n+2, fZone2Code, fout);
            printlines(n+2, fZone2bCode, fout);
            printlines(n+2, fZone3Code, fout);
            printLoopGraphInternal (n+2,fout);
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
		tab(n+1,fout); fout << "int fSamplingFreq;";

		for (k = fSubClassList.begin(); k != fSubClassList.end(); k++) 	(*k)->println(n+1, fout);

		printlines(n+1, fDeclCode, fout);

	tab(n,fout); fout << "  public:";

		tab(n+1,fout); fout << "int getNumInputs() { "
						<< "return " << fNumInputs << "; }";
		tab(n+1,fout); fout << "int getNumOutputs() { "
						<< "return " << fNumOutputs << "; }";

		tab(n+1,fout); fout << "void init(int samplingFreq) {";
			tab(n+2,fout); fout << "fSamplingFreq = samplingFreq;";
			printlines(n+2, fInitCode, fout);
            printlines(n+2, fClearCode, fout);
		tab(n+1,fout); fout << "}";

		tab(n+1,fout); fout << subst("void fill (int count, $0 output[]) {", ifloat());
            printlines(n+2, fZone1Code, fout);
            printlines(n+2, fZone2Code, fout);
            printlines(n+2, fZone2bCode, fout);
            printlines(n+2, fZone3Code, fout);
            printLoopGraphInternal(n+2,fout);
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
	list<Klass* >::iterator k;

	for (k = fSubClassList.begin(); k != fSubClassList.end(); k++) 	(*k)->collectIncludeFile(S);
	merge(S, fIncludeFileSet);
}

void Klass::collectLibrary(set<string>& S)
{
	list<Klass* >::iterator k;

	for (k = fSubClassList.begin(); k != fSubClassList.end(); k++) 	(*k)->collectLibrary(S);
	merge(S, fLibrarySet);
}
