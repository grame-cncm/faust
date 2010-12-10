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
			- code_gen.h : generic code generator (projet FAUST) -


		Historique :
		-----------

***********************************************************************/
#include <string>
#include <list>
#include <set>
#include <map>
#include <vector>

#include "code_container.hh"
#include "floats.hh"

using namespace std;

extern bool gOpenMPLoop;
extern bool gDeepFirstSwitch;
extern bool gFunTaskSwitch;
extern bool gDSPStruct;

// Basic type creation
map<Typed::VarType, BasicTyped*> BasicTyped::gTypeTable;

// Table of all declared variables during one evaluation
map<string, Typed*> gVarTable;

CodeContainer::CodeContainer(int numInputs, int numOutputs)
    :fNumInputs(numInputs), fNumOutputs(numOutputs),
    fInputRates(numInputs), fOutputRates(numOutputs),
    fExtGlobalDeclarationInstructions(InstBuilder::genBlockInst()),
    fGlobalDeclarationInstructions(InstBuilder::genBlockInst()),
    fDeclarationInstructions(InstBuilder::genBlockInst()),
    fInitInstructions(InstBuilder::genBlockInst()),
    fDestroyInstructions(InstBuilder::genBlockInst()),
    fStaticInitInstructions(InstBuilder::genBlockInst()),
    fComputeBlockInstructions(InstBuilder::genBlockInst()),
    fComputeFunctions(InstBuilder::genBlockInst()),
    fUserInterfaceInstructions(InstBuilder::genBlockInst()),
    fSubContainerType(kInt)
{
    fCurLoop = new CodeLoop(0, "i");
}

CodeContainer::CodeContainer()
    :fNumInputs(2), fNumOutputs(2),
    fInputRates(2), fOutputRates(2),
    fExtGlobalDeclarationInstructions(InstBuilder::genBlockInst()),
    fGlobalDeclarationInstructions(InstBuilder::genBlockInst()),
    fDeclarationInstructions(InstBuilder::genBlockInst()),
    fInitInstructions(InstBuilder::genBlockInst()),
    fDestroyInstructions(InstBuilder::genBlockInst()),
    fStaticInitInstructions(InstBuilder::genBlockInst()),
    fComputeBlockInstructions(InstBuilder::genBlockInst()),
    fComputeFunctions(InstBuilder::genBlockInst()),
    fUserInterfaceInstructions(InstBuilder::genBlockInst()),
    fSubContainerType(kInt)
{
    fCurLoop = new CodeLoop(0, "i");
}

CodeContainer::~CodeContainer()
{
    delete fCurLoop;
}

void CodeContainer::transformDAG(DispatchVisitor* visitor)
{
    lclgraph G;
    CodeLoop::sortGraph(fCurLoop, G);
    for (int l = G.size() - 1; l >= 0; l--) {
        for (lclset::const_iterator p = G[l].begin(); p != G[l].end(); p++) {
            (*p)->transform(visitor);
        }
    }
}

/**
 * Store the loop used to compute a signal
 */
void CodeContainer::setLoopProperty(Tree sig, CodeLoop* l)
{
    fLoopProperty.set(sig, l);
}

/**
 * Returns the loop used to compute a signal
 */
bool CodeContainer::getLoopProperty(Tree sig, CodeLoop*& l)
{
    return fLoopProperty.get(sig, l);
}

/**
 * Open a non-recursive loop on top of the stack of open loops.
 * @param size the number of iterations of the loop
 */
void CodeContainer::openLoop(string index_name, int size)
{
    fCurLoop = new CodeLoop(fCurLoop, index_name, size);
}

/**
 * Open a recursive loop on top of the stack of open loops.
 * @param recsymbol the recursive symbol defined in this loop
 * @param size the number of iterations of the loop
 */
void CodeContainer::openLoop(Tree recsymbol, string index_name, int size)
{
     fCurLoop = new CodeLoop(recsymbol, fCurLoop, index_name, size);
}

/**
 * Close the top loop and either keep it
 * or absorb it within its enclosing loop.
 */
void CodeContainer::closeLoop(Tree sig)
{
    assert(fCurLoop);
    CodeLoop* l = fCurLoop;
    fCurLoop = l->fEnclosingLoop;
    assert(fCurLoop);

    if (l->isEmpty() || l->hasRecDependencies()) {
        fCurLoop->absorb(l);
        delete l;
    } else {
        // we have an independent loop
		if (sig) {
			setLoopProperty(sig, l);     // associate the signal
		} else {
			//cerr << "***ERROR**** no signal for loop "<< l << endl;
		}
        fCurLoop->fBackwardLoopDependencies.insert(l);
    }
}

/**
 * Print the required C++ libraries as comments in source code
 */
void CodeContainer::printLibrary(ostream& fout)
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
void CodeContainer::printIncludeFile(ostream& fout)
{
    set<string> S;
    set<string>::iterator f;

    collectIncludeFile(S);
    for (f = S.begin(); f != S.end(); f++) 	{
        fout << "#include " << *f << "\n";
    }
}

/**
 * Print the loop graph in dot format
 */
void CodeContainer::printGraphDotFormat(ostream& fout)
{
    lclgraph G;
    CodeLoop::sortGraph(fCurLoop, G);

    fout << "strict digraph loopgraph {" << endl;
    fout << '\t' << "rankdir=LR;" << endl;
    fout << '\t' << "node[color=blue, fillcolor=lightblue, style=filled, fontsize=9];" << endl;

    int lnum = 0;       // used for loop numbers
    // for each level of the graph
    for (int l = G.size() - 1; l >= 0; l--) {
        // for each task in the level
        for (lclset::const_iterator t = G[l].begin(); t!=G[l].end(); t++) {
            // print task label "Lxxx : 0xffffff"
            fout << '\t' << 'L'<<(*t)<<"[label=<<font face=\"verdana,bold\">L"<<lnum++<<"</font> : "<<(*t)<<">];"<<endl;
            // for each source of the task
            for (lclset::const_iterator src = (*t)->fBackwardLoopDependencies.begin(); src!=(*t)->fBackwardLoopDependencies.end(); src++) {
                // print the connection Lxxx -> Lyyy;
                fout << '\t' << 'L'<<(*src)<<"->"<<'L'<<(*t)<<';'<<endl;
            }
        }
    }
    fout << "}" << endl;
}

/**
 *  Add forward dependencies in the DAG
 */
 void CodeContainer::computeForwardDAG(lclgraph dag)
{
    #define START_TASK_MAX 2

    int loop_num = START_TASK_MAX; // First index to be used for remaining tasks

    for (int l = dag.size() - 1; l >= 0; l--) {
        for (lclset::const_iterator p = dag[l].begin(); p != dag[l].end(); p++) {
            for (lclset::const_iterator p1 = (*p)->fBackwardLoopDependencies.begin(); p1!=(*p)->fBackwardLoopDependencies.end(); p1++) {
                (*p1)->fForwardLoopDependencies.insert((*p));
            }
            (*p)->fIndex = loop_num;
            loop_num++;
        }
    }
}

ValueInst* CodeContainer::pushFunction(const string& name, Typed::VarType result, vector<Typed::VarType>& types, const list<ValueInst*>& args)
{
    BasicTyped* result_type = InstBuilder::genBasicTyped(result);

    // Special case for "faustpower"
    if (name == "faustpower") {

        list<NamedTyped*> named_args;
        named_args.push_back(InstBuilder::genNamedTyped("value", InstBuilder::genBasicTyped(types[0])));

        list<ValueInst*>::const_iterator it = args.begin();
        it++;
        IntNumInst* arg1 = dynamic_cast<IntNumInst*>(*it);
        assert(arg1);

        stringstream num; num << arg1->fNum;
        string faust_power = name + num.str();

        // Expand the pow depending of the exposant argument
        BlockInst* block = InstBuilder::genBlockInst();

        if (arg1->fNum == 0) {
             block->pushBackInst(InstBuilder::genRetInst(InstBuilder::genIntNumInst(1)));
        } else {
            ValueInst* res = InstBuilder::genLoadFunArgsVar("value");
            for (int i= 0; i < arg1->fNum - 1; i++) {
                res = InstBuilder::genMul(res, InstBuilder::genLoadFunArgsVar("value"));
            }
            block->pushBackInst(InstBuilder::genRetInst(res));
        }

        fGlobalDeclarationInstructions->pushBackInst(InstBuilder::genDeclareFunInst(faust_power, InstBuilder::genFunTyped(named_args, result_type), block));
        list<ValueInst*> truncated_args;
        truncated_args.push_back((*args.begin()));
        return InstBuilder::genFunCallInst(faust_power, truncated_args);

    } else {

        list<NamedTyped*> named_args;
        for (size_t i = 0; i < types.size(); i++) {
            stringstream num; num << i;
            named_args.push_back(InstBuilder::genNamedTyped("dummy" + num.str(), InstBuilder::genBasicTyped(types[i])));
        }

        fGlobalDeclarationInstructions->pushBackInst(InstBuilder::genDeclareFunInst(name, InstBuilder::genFunTyped(named_args, result_type)));
        return InstBuilder::genFunCallInst(name, args);
    }
}

void CodeContainer::sortDeepFirstDAG(CodeLoop* l, set<CodeLoop*>& visited, list<CodeLoop*>& result)
{
	// Avoid printing already printed loops
	if (isElement(visited, l)) return;

	// Remember we have printed this loop
	visited.insert(l);

	// Compute the dependencies loops (that need to be computed before this one)
	for (lclset::const_iterator p = l->fBackwardLoopDependencies.begin(); p != l->fBackwardLoopDependencies.end(); p++) {
        sortDeepFirstDAG(*p, visited, result);
    }

    // Keep the non-empty loops in result
    if (!l->isEmpty())
        result.push_back(l);
}

void CodeContainer::generateLocalInputs(BlockInst* loop_code)
{
    // Generates line like: FAUSTFLOAT* input0 = &input0_ptr[index];
    for (int index = 0; index < inputs(); index++) {
        string name1 = subst("fInput$0", T(index));
        string name2 = subst("fInput$0_ptr", T(index));
        loop_code->pushBackInst(InstBuilder::genStoreStructVar(name1, InstBuilder::genLoadArrayStructAddressVar(name2, InstBuilder::genLoadLoopVar("index"))));
    }
}

void CodeContainer::generateLocalOutputs(BlockInst* loop_code)
{
    // Generates line like: FAUSTFLOAT* ouput0 = &ouput0_ptr[index];
    for (int index = 0; index < outputs(); index++) {
        string name1 = subst("fOutput$0", T(index));
        string name2 = subst("fOutput$0_ptr", T(index));
        loop_code->pushBackInst(InstBuilder::genStoreStructVar(name1, InstBuilder::genLoadArrayStructAddressVar(name2, InstBuilder::genLoadLoopVar("index"))));
    }
}

void CodeContainer::generateDAGLoopAux(CodeLoop* loop, BlockInst* loop_code, int loop_num, bool omp)
{
    if (gFunTaskSwitch) {
        BlockInst* block = InstBuilder::genBlockInst();

        loop->generateDAGLoop(block, omp);
        /*
        if (loop->fIsRecursive)
            loop->generateDAGLoop(block, omp);
        else
            loop->generateDAGVecLoop(block, omp, 4);
        */
        Loop2FunctionBuider builder(subst("fun$0", T(loop_num)), block, gDSPStruct);
        fComputeFunctions->pushBackInst(builder.fFunctionDef);
        loop_code->pushBackInst(InstBuilder::genLabelInst((loop->fIsRecursive) ? subst("// Recursive function $0", T(loop_num)) : subst("// Vectorizable function $0", T(loop_num))));
        loop_code->pushBackInst(builder.fFunctionCall);
    } else {
        loop_code->pushBackInst(InstBuilder::genLabelInst((loop->fIsRecursive) ? subst("// Recursive loop $0", T(loop_num)) : subst("// Vectorizable loop $0", T(loop_num))));

        loop->generateDAGLoop(loop_code, omp);
        /*
        if (loop->fIsRecursive)
            loop->generateDAGLoop(loop_code, omp);
        else
            loop->generateDAGVecLoop(loop_code, omp, 4);
        */
    }
}

void CodeContainer::generateDAGLoop(BlockInst* block)
{
    int loop_num = 0;

    if (gDeepFirstSwitch) {
        set<CodeLoop*> visited;
        list<CodeLoop*> result;
        sortDeepFirstDAG(fCurLoop, visited, result);
        for (list<CodeLoop*>::const_iterator p = result.begin(); p != result.end(); p++) {
            generateDAGLoopAux(*p, block, loop_num++);
        }
    } else {
        lclgraph G;
        CodeLoop::sortGraph(fCurLoop, G);
        for (int l = G.size() - 1; l >= 0; l--) {
            for (lclset::const_iterator p = G[l].begin(); p != G[l].end(); p++) {
                generateDAGLoopAux(*p, block, loop_num++);
            }
        }
    }
}

bool CodeContainer::sortArrayDeclarations(StatementInst* a, StatementInst* b)
{
    if (dynamic_cast<DeclareVarInst*>(a)) {
        DeclareVarInst* inst = dynamic_cast<DeclareVarInst*>(a);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fTyped);
        return (array_typed) ? (array_typed->fSize > 0) : false;
    } else if (dynamic_cast<DeclareVarInst*>(b)) {
        DeclareVarInst* inst = dynamic_cast<DeclareVarInst*>(a);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fTyped);
        return (array_typed) ? (array_typed->fSize > 0) : false;
    } else {
        return false;
    }
}

