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
#include "recursivness.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

// Basic type creation
map<Typed::VarType, BasicTyped*> BasicTyped::gTypeTable;

// Table of all declared variables during one evaluation
map<string, Typed*> gVarTable;

void CodeContainer::initializeCodeContainer(int numInputs, int numOutputs)
{
    fNumInputs = numInputs;
    fNumOutputs = numOutputs;
    fInputRates.resize(numInputs, 0);
    fOutputRates.resize(numOutputs, 0);
}

CodeContainer::CodeContainer()
    :fNumInputs(-1), fNumOutputs(-1),
    fExtGlobalDeclarationInstructions(InstBuilder::genBlockInst()),
    fGlobalDeclarationInstructions(InstBuilder::genBlockInst()),
    fDeclarationInstructions(InstBuilder::genBlockInst()),
    fInitInstructions(InstBuilder::genBlockInst()),
    fPostInitInstructions(InstBuilder::genBlockInst()),
    fDestroyInstructions(InstBuilder::genBlockInst()),
    fStaticInitInstructions(InstBuilder::genBlockInst()),
    fPostStaticInitInstructions(InstBuilder::genBlockInst()),
    fComputeBlockInstructions(InstBuilder::genBlockInst()),
    fComputeFunctions(InstBuilder::genBlockInst()),
    fUserInterfaceInstructions(InstBuilder::genBlockInst()),
    fSubContainerType(kInt), fFullCount("count"),
    fGeneratedSR(false)
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
    assert(sig);
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

    Tree S = symlist(sig);
    if (l->isEmpty() || fCurLoop->hasRecDependencyIn(S)) {
        fCurLoop->absorb(l);
        //delete l; HACK !!!
    } else {
        // cout << " will NOT absorb" << endl;
        // we have an independent loop
        setLoopProperty(sig, l);     // associate the signal
        fCurLoop->fBackwardLoopDependencies.insert(l);
        // we need to indicate that all recursive symbols defined
        // in this loop are defined in this loop
        for (Tree lsym = l->fRecSymbolSet; !isNil(lsym); lsym = tl(lsym)) {
            this->setLoopProperty(hd(lsym), l);
            //cerr << "loop " << l << " defines " << *hd(lsym) << endl;
        }
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
    if (S.size() > 0) {
        fout << "/* link with ";
        for (f = S.begin(), sep =": "; f != S.end(); f++, sep = ", ") 	{
            fout << sep << *f;
        }
        fout << " */\n";
    }
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

    // Special case for "faustpower", generates sequence of multiplications
    if (name == "faustpower") {

        list<NamedTyped*> named_args;
        named_args.push_back(InstBuilder::genNamedTyped("value", InstBuilder::genBasicTyped(types[0])));

        list<ValueInst*>::const_iterator it = args.begin();
        it++;
        IntNumInst* arg1 = dynamic_cast<IntNumInst*>(*it);
        assert(arg1);
        assert(arg1->fNum > 0);

        stringstream num;
        num << arg1->fNum;
        string faust_power = name + num.str() + ((result == Typed::kInt) ? "_i" : "_f");

        if (gPowerGlobalTable.find(faust_power) == gPowerGlobalTable.end()) {

            BlockInst* global_block = InstBuilder::genBlockInst();

            global_block->pushBackInst(InstBuilder::genLabelInst("#ifndef __" + faust_power + "__"));
            global_block->pushBackInst(InstBuilder::genLabelInst("#define __" + faust_power + "__"));

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

            global_block->pushBackInst(InstBuilder::genDeclareFunInst(faust_power, InstBuilder::genFunTyped(named_args, result_type), block));
            fGlobalDeclarationInstructions->pushBackInst(global_block);

            global_block->pushBackInst(InstBuilder::genLabelInst("#endif"));

            // First declaration
            gPowerGlobalTable[faust_power] = 1;
         }

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

DeclareFunInst* CodeContainer::generateGetInputs(const string& name, bool isvirtual)
{
    list<NamedTyped*> args;
    BlockInst* block = InstBuilder::genBlockInst();
    block->pushBackInst(InstBuilder::genRetInst(InstBuilder::genIntNumInst(fNumInputs)));

    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kInt), (isvirtual) ? FunTyped::kVirtual : FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* CodeContainer::generateGetOutputs(const string& name, bool isvirtual)
{
    list<NamedTyped*> args;
    BlockInst* block = InstBuilder::genBlockInst();
    block->pushBackInst(InstBuilder::genRetInst(InstBuilder::genIntNumInst(fNumOutputs)));

    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kInt), (isvirtual) ? FunTyped::kVirtual : FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* CodeContainer::generateGetInputRate(const string& name, bool isvirtual)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped("channel", Typed::kInt));

    BlockInst* code = InstBuilder::genBlockInst();
    ValueInst* switch_cond = InstBuilder::genLoadFunArgsVar("channel");
    ::SwitchInst* switch_block = InstBuilder::genSwitchInst(switch_cond);
    code->pushBackInst(switch_block);

    int i = 0;
    for (vector<int>::const_iterator it = fInputRates.begin(); it != fInputRates.end(); it++, i++) {
        // Creates "case" block
        BlockInst* case_block = InstBuilder::genBlockInst();
        // Compiles "case" block
        case_block->pushBackInst(InstBuilder::genRetInst(InstBuilder::genIntNumInst(*it)));
        // Add it into the switch
        switch_block->addCase(i, case_block);
    }

    // Default case
    BlockInst* default_case_block = InstBuilder::genBlockInst();
    default_case_block->pushBackInst(InstBuilder::genRetInst(InstBuilder::genIntNumInst(-1)));
    switch_block->addCase(-1, default_case_block);

    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kInt), (isvirtual) ? FunTyped::kVirtual : FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, code);
}

DeclareFunInst* CodeContainer::generateGetOutputRate(const string& name, bool isvirtual)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped("channel", Typed::kInt));

    BlockInst* code = InstBuilder::genBlockInst();
    ValueInst* switch_cond = InstBuilder::genLoadFunArgsVar("channel");
    ::SwitchInst* switch_block = InstBuilder::genSwitchInst(switch_cond);
    code->pushBackInst(switch_block);

    int i = 0;
    for (vector<int>::const_iterator it = fOutputRates.begin(); it != fOutputRates.end(); it++, i++) {
        // Creates "case" block
        BlockInst* case_block = InstBuilder::genBlockInst();
        // Compiles "case" block
        case_block->pushBackInst(InstBuilder::genRetInst(InstBuilder::genIntNumInst(*it)));
        // Add it into the switch
        switch_block->addCase(i, case_block);
    }

    // Default case
    BlockInst* default_case_block = InstBuilder::genBlockInst();
    default_case_block->pushBackInst(InstBuilder::genRetInst(InstBuilder::genIntNumInst(-1)));
    switch_block->addCase(-1, default_case_block);

    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kInt), (isvirtual) ? FunTyped::kVirtual : FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, code);
}

void CodeContainer::generateDAGLoopInternal(CodeLoop* loop, BlockInst* block, DeclareVarInst * count, bool omp)
{
    if (gGlobal->gVecLoopSize > 0 && !loop->fIsRecursive) {
        loop->generateDAGVectorLoop(block, count, omp, gGlobal->gVecLoopSize);
    } else {
        loop->generateDAGScalarLoop(block, count, omp);
    }
}

void CodeContainer::generateDAGLoopAux(CodeLoop* loop, BlockInst* loop_code, DeclareVarInst * count, int loop_num, bool omp)
{
    if (gGlobal->gFunTaskSwitch) {
        BlockInst* block = InstBuilder::genBlockInst();
        // Generates scalar or vectorized loop
        generateDAGLoopInternal(loop, block, count, omp);
        Loop2FunctionBuider builder(subst("fun$0" + getClassName(), T(loop_num)), block, gGlobal->gDSPStruct);
        fComputeFunctions->pushBackInst(builder.fFunctionDef);
        loop_code->pushBackInst(InstBuilder::genLabelInst((loop->fIsRecursive) ? subst("/* Recursive function $0 */", T(loop_num)) : subst("/* Vectorizable function $0 */", T(loop_num))));
        loop_code->pushBackInst(builder.fFunctionCall);
    } else {
        loop_code->pushBackInst(InstBuilder::genLabelInst((loop->fIsRecursive) ? subst("/* Recursive loop $0 */", T(loop_num)) : subst("/* Vectorizable loop $0 */", T(loop_num))));
        // Generates scalar or vectorized loop
        generateDAGLoopInternal(loop, loop_code, count, omp);
    }
}

void CodeContainer::generateDAGLoop(BlockInst* block, DeclareVarInst* count)
{
    int loop_num = 0;

    if (gGlobal->gDeepFirstSwitch) {
        set<CodeLoop*> visited;
        list<CodeLoop*> result;
        sortDeepFirstDAG(fCurLoop, visited, result);
        for (list<CodeLoop*>::const_iterator p = result.begin(); p != result.end(); p++) {
            generateDAGLoopAux(*p, block, count, loop_num++);
        }
    } else {
        lclgraph G;
        CodeLoop::sortGraph(fCurLoop, G);
        for (int l = G.size() - 1; l >= 0; l--) {
            for (lclset::const_iterator p = G[l].begin(); p != G[l].end(); p++) {
                generateDAGLoopAux(*p, block, count, loop_num++);
            }
        }
    }
}

void CodeContainer::processFIR(void)
{
    if (gGlobal->gGroupTaskSwitch) {
        CodeLoop::computeUseCount(fCurLoop);
        CodeLoop::groupSeqLoops(fCurLoop);
    }
}
