/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#include <fstream>
#include <string>

#include "code_container.hh"
#include "fir_to_fir.hh"
#include "floats.hh"
#include "global.hh"
#include "recursivness.hh"
#include "text_instructions.hh"
#include "type_manager.hh"

using namespace std;

void CodeContainer::initialize(int numInputs, int numOutputs)
{
    fNumInputs  = numInputs;
    fNumOutputs = numOutputs;
    fInputRates.resize(numInputs, 0);
    fOutputRates.resize(numOutputs, 0);
}

CodeContainer::CodeContainer()
    : fParentContainer(0),
      fNumInputs(-1),
      fNumOutputs(-1),
      fNumActives(0),
      fNumPassives(0),
      fSubContainerType(kInt),
      fGeneratedSR(false),
      fExtGlobalDeclarationInstructions(InstBuilder::genBlockInst()),
      fGlobalDeclarationInstructions(InstBuilder::genBlockInst()),
      fDeclarationInstructions(InstBuilder::genBlockInst()),
      fInitInstructions(InstBuilder::genBlockInst()),
      fResetUserInterfaceInstructions(InstBuilder::genBlockInst()),
      fClearInstructions(InstBuilder::genBlockInst()),
      fPostInitInstructions(InstBuilder::genBlockInst()),
      fAllocateInstructions(InstBuilder::genBlockInst()),
      fDestroyInstructions(InstBuilder::genBlockInst()),
      fStaticInitInstructions(InstBuilder::genBlockInst()),
      fPostStaticInitInstructions(InstBuilder::genBlockInst()),
      fStaticDestroyInstructions(InstBuilder::genBlockInst()),
      fComputeBlockInstructions(InstBuilder::genBlockInst()),
      fPostComputeBlockInstructions(InstBuilder::genBlockInst()),
      fComputeFunctions(InstBuilder::genBlockInst()),
      fUserInterfaceInstructions(InstBuilder::genBlockInst()),
      fInt32ControlNum(0),
      fRealControlNum(0)
{
    fCurLoop = new CodeLoop(0, "i");
}

CodeContainer::~CodeContainer()
{}

void CodeContainer::transformDAG(DispatchVisitor* visitor)
{
    lclgraph G;
    CodeLoop::sortGraph(fCurLoop, G);
    for (int l = int(G.size() - 1); l >= 0; l--) {
        for (auto& p : G[l]) {
            p->transform(visitor);
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
    faustassert(sig);
    return fLoopProperty.get(sig, l);
}

void CodeContainer::listAllLoopProperties(Tree sig, set<CodeLoop*>& L, set<Tree>& visited)
{
    if (visited.count(sig) == 0) {
        visited.insert(sig);
        CodeLoop* l;
        if (getLoopProperty(sig, l)) {
            L.insert(l);
        } else {
            // we go down the expression
            vector<Tree> subsigs;
            int          n = getSubSignals(sig, subsigs, false);
            for (int i = 0; i < n; i++) {
                listAllLoopProperties(subsigs[i], L, visited);
            }
        }
    }
}

/**
 * Open a non-recursive loop on top of the stack of open loops.
 * @param size the number of iterations of the loop
 */
void CodeContainer::openLoop(const string& index_name, int size)
{
    fCurLoop = new CodeLoop(fCurLoop, index_name, size);
}

/**
 * Open a recursive loop on top of the stack of open loops.
 * @param recsymbol the recursive symbol defined in this loop
 * @param size the number of iterations of the loop
 */
void CodeContainer::openLoop(Tree recsymbol, const string& index_name, int size)
{
    fCurLoop = new CodeLoop(recsymbol, fCurLoop, index_name, size);
}

/**
 * Close the top loop and either keep it
 * or absorb it within its enclosing loop.
 */
void CodeContainer::closeLoop(Tree sig)
{
    faustassert(fCurLoop);
    
    // fix the missing dependencies
    set<CodeLoop*> L;
    set<Tree> V;
    listAllLoopProperties(sig, L, V);
    for (CodeLoop* l : L) {
        fCurLoop->fBackwardLoopDependencies.insert(l);
    }
    
    CodeLoop* l = fCurLoop;
    fCurLoop    = l->fEnclosingLoop;
    faustassert(fCurLoop);

    Tree S = symlist(sig);
    if (l->isEmpty() || fCurLoop->hasRecDependencyIn(S)) {
        fCurLoop->absorb(l);
    } else {
        // cout << " will NOT absorb" << endl;
        // we have an independent loop
        setLoopProperty(sig, l);  // associate the signal
        fCurLoop->fBackwardLoopDependencies.insert(l);
        // we need to indicate that all recursive symbols defined
        // in this loop are defined in this loop
        for (Tree lsym = l->fRecSymbolSet; !isNil(lsym); lsym = tl(lsym)) {
            this->setLoopProperty(hd(lsym), l);
            // cerr << "loop " << l << " defines " << *hd(lsym) << endl;
        }
    }
}

/**
 * Print the required C++ libraries as comments in source code
 */
void CodeContainer::printLibrary(ostream& fout)
{
    set<string>           S;
    set<string>::iterator f;

    string sep;
    collectLibrary(S);
    if (S.size() > 0) {
        fout << "/* link with ";
        for (f = S.begin(), sep = ": "; f != S.end(); f++, sep = ", ") {
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
    set<string>           S;
    set<string>::iterator f;

    collectIncludeFile(S);
    for (f = S.begin(); f != S.end(); f++) {
        string inc = *f;
        // Only print non-empty include (inc is actually quoted)
        if (inc.size() > 2) {
            fout << "#include " << *f << "\n";
        }
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

    int lnum = 0;  // used for loop numbers
    // for each level of the graph
    for (int l = int(G.size() - 1); l >= 0; l--) {
        // for each task in the level
        for (auto& t : G[l]) {
            // print task label "Lxxx : 0xffffff"
            fout << '\t' << 'L' << t << "[label=<<font face=\"verdana,bold\">L"
                 << lnum++ << "</font> : " << t
                 << ">];" << endl;
            // for each source of the task
            for (auto& src : t->fBackwardLoopDependencies) {
                // print the connection Lxxx -> Lyyy;
                fout << '\t' << 'L' << src << "->" << 'L' << t << ';' << endl;
            }
        }
    }
    fout << "}" << endl;
}

/**
 *  Adds forward dependencies in the DAG and returns loop count
 */
void CodeContainer::computeForwardDAG(lclgraph dag, int& loop_count, vector<int>& ready_loop)
{
#define START_TASK_MAX 2

    int loop_index = START_TASK_MAX;  // First index to be used for remaining tasks

    for (int l = int(dag.size() - 1); l >= 0; l--) {
        for (auto& p : dag[l]) {
            // Setup forward dependancy
            for (auto& p1 : p->fBackwardLoopDependencies) {
                p1->fForwardLoopDependencies.insert(p);
            }

            // Setup loop index
            p->fIndex = loop_index;
            loop_index++;

            // Keep ready loops
            if (p->getBackwardLoopDependencies().size() == 0) {
                ready_loop.push_back(p->getIndex());
            }
        }
    }

    loop_count = loop_index;
}

ValueInst* CodeContainer::pushFunction(const string& name, Typed::VarType result, vector<Typed::VarType>& types,
                                       const list<ValueInst*>& args)
{
    list<NamedTyped*> named_args;
    for (size_t i = 0; i < types.size(); i++) {
        named_args.push_back(InstBuilder::genNamedTyped("dummy" + to_string(i), InstBuilder::genBasicTyped(types[i])));
    }
    pushGlobalDeclare(InstBuilder::genDeclareFunInst(name, InstBuilder::genFunTyped(named_args, InstBuilder::genBasicTyped(result))));
    return InstBuilder::genFunCallInst(name, args);
}

void CodeContainer::sortDeepFirstDAG(CodeLoop* l, set<CodeLoop*>& visited, list<CodeLoop*>& result)
{
    // Avoid printing already printed loops
    if (isElement(visited, l)) return;

    // Remember we have printed this loop
    visited.insert(l);

    // Compute the dependencies loops (that need to be computed before this one)
    for (auto& p : l->fBackwardLoopDependencies) {
        sortDeepFirstDAG(p, visited, result);
    }

    // Keep the non-empty loops in result
    if (!l->isEmpty()) {
        result.push_back(l);
    }
}

// Functions are coded with a "class" prefix, so to stay separated in "gGlobalTable"
void CodeContainer::produceInfoFunctions(int tabs, const string& classname, const string& obj, bool ismethod,
                                         bool isvirtual, TextInstVisitor* producer)
{
    // Input/Output method
    producer->Tab(tabs);
    generateGetInputs(subst("getNumInputs$0", classname), obj, ismethod, isvirtual)->accept(producer);
    generateGetOutputs(subst("getNumOutputs$0", classname), obj, ismethod, isvirtual)->accept(producer);

    /*
    // 03/04/21: suppressed fo now
    // Input Rates
    producer->Tab(tabs);
    generateGetInputRate(subst("getInputRate$0", classname), obj, ismethod, isvirtual)->accept(producer);

    // Output Rates
    producer->Tab(tabs);
    generateGetOutputRate(subst("getOutputRate$0", classname), obj, ismethod, isvirtual)->accept(producer);
    */
}

void CodeContainer::generateDAGLoopInternal(CodeLoop* loop, BlockInst* block, DeclareVarInst* count, bool omp)
{
    loop->generateDAGScalarLoop(block, count, omp);
}

void CodeContainer::generateDAGLoopAux(CodeLoop* loop, BlockInst* loop_code, DeclareVarInst* count, int loop_num,
                                       bool omp)
{
    if (gGlobal->gFunTaskSwitch) {
        BlockInst* block = InstBuilder::genBlockInst();
        // Generates scalar or vectorized loop
        generateDAGLoopInternal(loop, block, count, omp);
        Loop2FunctionBuider builder(subst("fun$0" + getClassName(), T(loop_num)), block, gGlobal->gDSPStruct);
        pushOtherComputeMethod(builder.fFunctionDef);
        loop_code->pushBackInst(InstBuilder::genLabelInst((loop->fIsRecursive)
                                                              ? subst("/* Recursive function $0 */", T(loop_num))
                                                              : subst("/* Vectorizable function $0 */", T(loop_num))));
        loop_code->pushBackInst(builder.fFunctionCall);
    } else {
        loop_code->pushBackInst(InstBuilder::genLabelInst((loop->fIsRecursive)
                                                              ? subst("/* Recursive loop $0 */", T(loop_num))
                                                              : subst("/* Vectorizable loop $0 */", T(loop_num))));
        // Generates scalar or vectorized loop
        generateDAGLoopInternal(loop, loop_code, count, omp);
    }
}

void CodeContainer::generateDAGLoop(BlockInst* block, DeclareVarInst* count)
{
    int loop_num = 0;

    if (gGlobal->gDeepFirstSwitch) {
        set<CodeLoop*>  visited;
        list<CodeLoop*> result;
        sortDeepFirstDAG(fCurLoop, visited, result);
        for (auto& p : result) {
            generateDAGLoopAux(p, block, count, loop_num++);
        }
    } else {
        lclgraph G;
        CodeLoop::sortGraph(fCurLoop, G);
        for (int l = int(G.size() - 1); l >= 0; l--) {
            for (auto& p : G[l]) {
                generateDAGLoopAux(p, block, count, loop_num++);
            }
        }
    }
}

void CodeContainer::processFIR(void)
{
    // Types used in 'compute' prototype
    gGlobal->setVarType("count", Typed::kInt32);
    gGlobal->setVarType("inputs", Typed::kFloatMacro_ptr_ptr);
    gGlobal->setVarType("outputs", Typed::kFloatMacro_ptr_ptr);
    
    // Types used in 'compute' prototype in -os mode
    gGlobal->setVarType("iControl", Typed::kInt32_ptr);
    gGlobal->setVarType("fControl", Typed::kFloatMacro_ptr);
    
    // Possibly add "fSamplingRate" field
    generateSR();

    // Possibly groups tasks (used by VectorCodeContainer, OpenMPCodeContainer and WSSCodeContainer)
    if (gGlobal->gGroupTaskSwitch) {
        CodeLoop::computeUseCount(fCurLoop);
        set<CodeLoop*> visited;
        CodeLoop::groupSeqLoops(fCurLoop, visited);
    }

    // Sort struct fields by size and type
    // 05/16/17 : deactivated since it slows down the code...
    /*
     fDeclarationInstructions->fCode.sort(sortArrayDeclarations);
     fDeclarationInstructions->fCode.sort(sortTypeDeclarations);
     */
}

BlockInst* CodeContainer::flattenFIR(void)
{
    BlockInst* global_block = InstBuilder::genBlockInst();

    // Declaration part
    global_block->pushBackInst(InstBuilder::genLabelInst("========== Declaration part =========="));
    global_block->merge(fExtGlobalDeclarationInstructions);
    global_block->merge(fGlobalDeclarationInstructions);
    global_block->merge(fDeclarationInstructions);

    // Init method
    global_block->pushBackInst(InstBuilder::genLabelInst("========== Init method =========="));
    global_block->merge(fInitInstructions);
    global_block->merge(fResetUserInterfaceInstructions);
    global_block->merge(fClearInstructions);
    global_block->merge(fPostInitInstructions);

    // Static init method
    global_block->pushBackInst(InstBuilder::genLabelInst("========== Static init method =========="));
    global_block->merge(fStaticInitInstructions);
    global_block->merge(fPostStaticInitInstructions);

    // Subcontainers
    global_block->pushBackInst(InstBuilder::genLabelInst("========== Subcontainers =========="));
    for (auto& it : fSubContainers) {
        global_block->merge(it->flattenFIR());
    }

    // Compute method
    global_block->pushBackInst(InstBuilder::genLabelInst("========== Compute control =========="));
    global_block->merge(fComputeBlockInstructions);
    global_block->pushBackInst(InstBuilder::genLabelInst("========== Compute DSP =========="));
    global_block->pushBackInst(fCurLoop->generateScalarLoop(fFullCount));
    global_block->pushBackInst(InstBuilder::genLabelInst("========== Post compute DSP =========="));
    global_block->merge(fPostComputeBlockInstructions);

    return global_block;
}

BlockInst* CodeContainer::inlineSubcontainersFunCalls(BlockInst* block)
{
    // Rename 'sig' in 'dsp' and remove 'dsp' allocation
    block = DspRenamer().getCode(block);
    //dump2FIR(block);

    // Inline subcontainers 'instanceInit' and 'fill' function call
    for (auto& it : fSubContainers) {
        // Build the function to be inlined (prototype and code)
        DeclareFunInst* inst_init_fun = it->generateInstanceInitFun("instanceInit" + it->getClassName(), "dsp", true, false);
        //dump2FIR(inst_init_fun);
        block = FunctionCallInliner(inst_init_fun).getCode(block);
        //dump2FIR(block);
    
        // Build the function to be inlined (prototype and code)
        DeclareFunInst* fill_fun = it->generateFillFun("fill" + it->getClassName(), "dsp", true, false);
        //dump2FIR(fill_fun);
        block = FunctionCallInliner(fill_fun).getCode(block);
        //dump2FIR(block);
    }

    // dump2FIR(block);
    return block;
}

void CodeContainer::printMacros(ostream& fout, int n)
{
    // generate user interface macros if needed
    if (gGlobal->gUIMacroSwitch) {
        if (gGlobal->gOutputLang == "c" || gGlobal->gOutputLang == "cpp") {
            tab(n, fout);
            fout << "#ifdef FAUST_UIMACROS";
            tab(n + 1, fout);
            tab(n + 1, fout);
            for (auto& it : gGlobal->gMetaDataSet) {
                if (it.first == tree("filename")) {
                    fout << "#define FAUST_FILE_NAME " << **(it.second.begin());
                    break;
                }
            }
            tab(n + 1, fout);
            fout << "#define FAUST_CLASS_NAME " << "\"" << fKlassName << "\"";
            tab(n + 1, fout);
            fout << "#define FAUST_INPUTS " << fNumInputs;
            tab(n + 1, fout);
            fout << "#define FAUST_OUTPUTS " << fNumOutputs;
            tab(n + 1, fout);
            fout << "#define FAUST_ACTIVES " << fNumActives;
            tab(n + 1, fout);
            fout << "#define FAUST_PASSIVES " << fNumPassives;
            tab(n, fout);
            printlines(n + 1, fUIMacro, fout);
            tab(n, fout);
            tab(n, fout);
            {
                fout << "\t" << "#define FAUST_LIST_ACTIVES(p) \\";
                printlines(n + 2, fUIMacroActives, fout);
                tab(n, fout);
                tab(n, fout);
            }
            {
                fout << "\t" << "#define FAUST_LIST_PASSIVES(p) \\";
                printlines(n + 2, fUIMacroPassives, fout);
                tab(n, fout);
                tab(n, fout);
            }
            fout << "#endif" << endl;
        } else if (gGlobal->gOutputLang == "rust") {
            fout << "pub const FAUST_INPUTS: i32 = " << fNumInputs << ";";
            tab(n, fout);
            fout << "pub const FAUST_OUTPUTS: i32 = " << fNumOutputs << ";";
            tab(n, fout);
            fout << "pub const FAUST_ACTIVES: i32 = " << fNumActives << ";";
            tab(n, fout);
            fout << "pub const FAUST_PASSIVES: i32 = " << fNumPassives << ";";
            tab(n, fout);
        } else {
            faustassert(false);
        }
    }
}

// DSP API generation

DeclareFunInst* CodeContainer::generateGetIO(const string& name, const string& obj, int io, bool ismethod,
                                             bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }
    BlockInst* block = InstBuilder::genBlockInst();
    block->pushBackInst(InstBuilder::genRetInst(InstBuilder::genInt32NumInst(io)));

    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genInt32Typed(),
                                                  (isvirtual) ? FunTyped::kVirtual : FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* CodeContainer::generateGetInputs(const string& name, const string& obj, bool ismethod, bool isvirtual)
{
    return generateGetIO(name, obj, fNumInputs, ismethod, isvirtual);
}

DeclareFunInst* CodeContainer::generateGetOutputs(const string& name, const string& obj, bool ismethod, bool isvirtual)
{
    return generateGetIO(name, obj, fNumOutputs, ismethod, isvirtual);
}

DeclareFunInst* CodeContainer::generateAllocate(const string& name, const string& obj, bool ismethod, bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }

    BlockInst* block = InstBuilder::genBlockInst();
    block->pushBackInst(fAllocateInstructions);

    // Explicit return
    block->pushBackInst(InstBuilder::genRetInst());

    // Creates function
    return InstBuilder::genVoidFunction(name, args, block, isvirtual);
}

DeclareFunInst* CodeContainer::generateDestroy(const string& name, const string& obj, bool ismethod, bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }

    BlockInst* block = InstBuilder::genBlockInst();
    block->pushBackInst(fDestroyInstructions);

    // Explicit return
    block->pushBackInst(InstBuilder::genRetInst());

    // Creates function
    return InstBuilder::genVoidFunction(name, args, block, isvirtual);
}

DeclareFunInst* CodeContainer::generateGetIORate(const string& name, const string& obj, vector<int>& io, bool ismethod,
                                                 bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }
    args.push_back(InstBuilder::genNamedTyped("channel", Typed::kInt32));

    BlockInst*    block        = InstBuilder::genBlockInst();
    ValueInst*    switch_cond  = InstBuilder::genLoadFunArgsVar("channel");
    ::SwitchInst* switch_block = InstBuilder::genSwitchInst(switch_cond);
    block->pushBackInst(InstBuilder::genDecStackVar("rate", InstBuilder::genInt32Typed()));
    block->pushBackInst(switch_block);

    int i = 0;
    for (auto& it : io) {
        // Creates "case" block
        BlockInst* case_block = InstBuilder::genBlockInst();
        // Compiles "case" block
        case_block->pushBackInst(InstBuilder::genStoreStackVar("rate", InstBuilder::genInt32NumInst(it)));
        // Add it into the switch
        switch_block->addCase(i++, case_block);
    }

    // Default case
    BlockInst* default_case_block = InstBuilder::genBlockInst();
    default_case_block->pushBackInst(InstBuilder::genStoreStackVar("rate", InstBuilder::genInt32NumInst(-1)));
    switch_block->addCase(-1, default_case_block);

    // Return "rate" result
    block->pushBackInst(InstBuilder::genRetInst(InstBuilder::genLoadStackVar("rate")));

    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genInt32Typed(),
                                                  (isvirtual) ? FunTyped::kVirtual : FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* CodeContainer::generateGetInputRate(const string& name, const string& obj, bool ismethod,
                                                    bool isvirtual)
{
    return generateGetIORate(name, obj, fInputRates, ismethod, isvirtual);
}

DeclareFunInst* CodeContainer::generateGetOutputRate(const string& name, const string& obj, bool ismethod,
                                                     bool isvirtual)
{
    return generateGetIORate(name, obj, fOutputRates, ismethod, isvirtual);
}

DeclareFunInst* CodeContainer::generateInstanceClear(const string& name, const string& obj, bool ismethod,
                                                     bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }

    BlockInst* block = InstBuilder::genBlockInst();
    block->pushBackInst(fClearInstructions);

    // Explicit return
    block->pushBackInst(InstBuilder::genRetInst());

    // Creates function
    return InstBuilder::genVoidFunction(name, args, block, isvirtual);
}

DeclareFunInst* CodeContainer::generateInstanceConstants(const string& name, const string& obj, bool ismethod,
                                                         bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }
    args.push_back(InstBuilder::genNamedTyped("sample_rate", Typed::kInt32));

    BlockInst* block = InstBuilder::genBlockInst();
    block->pushBackInst(fInitInstructions);

    // Explicit return
    block->pushBackInst(InstBuilder::genRetInst());

    // Creates function
    return InstBuilder::genVoidFunction(name, args, block, isvirtual);
}

DeclareFunInst* CodeContainer::generateStaticInitFun(const string& name, bool isstatic)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped("sample_rate", Typed::kInt32));

    BlockInst* block = InstBuilder::genBlockInst();
    block->pushBackInst(fStaticInitInstructions);
    block->pushBackInst(fPostStaticInitInstructions);

    //  20/11/16 : added in generateInstanceInitFun, is this needed here ?
    /*
    init_block->pushBackInst(fResetUserInterfaceInstructions);
    init_block->pushBackInst(fClearInstructions);
    */

    // Explicit return
    block->pushBackInst(InstBuilder::genRetInst());

    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genVoidTyped(),
                                                  (isstatic) ? FunTyped::kStatic : FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* CodeContainer::generateInstanceInitFun(const string& name, const string& obj, bool ismethod,
                                                       bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }
    args.push_back(InstBuilder::genNamedTyped("sample_rate", Typed::kInt32));

    BlockInst* init_block = InstBuilder::genBlockInst();
    init_block->pushBackInst(fInitInstructions);
    init_block->pushBackInst(fPostInitInstructions);
    init_block->pushBackInst(fResetUserInterfaceInstructions);
    init_block->pushBackInst(fClearInstructions);

    // Explicit return
    init_block->pushBackInst(InstBuilder::genRetInst());

    // Creates function
    return InstBuilder::genVoidFunction(name, args, init_block, isvirtual);
}

DeclareFunInst* CodeContainer::generateFillFun(const string& name, const string& obj, bool ismethod, bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }
    args.push_back(InstBuilder::genNamedTyped("count", Typed::kInt32));
    if (fSubContainerType == kInt) {
        args.push_back(InstBuilder::genNamedTyped(fTableName, Typed::kInt32_ptr));
    } else {
        args.push_back(InstBuilder::genNamedTyped(fTableName, itfloatptr()));
    }

    BlockInst* block = InstBuilder::genBlockInst();
    block->pushBackInst(fComputeBlockInstructions);
    block->pushBackInst(fCurLoop->generateScalarLoop("count"));

    // Explicit return
    block->pushBackInst(InstBuilder::genRetInst());

    // Creates function
    return InstBuilder::genVoidFunction(name, args, block, isvirtual);
}

DeclareFunInst* CodeContainer::generateInit(const string& name, const string& obj, bool ismethod, bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }
    args.push_back(InstBuilder::genNamedTyped("sample_rate", Typed::kInt32));

    BlockInst* block = InstBuilder::genBlockInst();
    {
        list<ValueInst*> args1;
        if (!ismethod) {
            args1.push_back(InstBuilder::genLoadFunArgsVar(obj));
        }
        args1.push_back(InstBuilder::genLoadFunArgsVar("sample_rate"));
        block->pushBackInst(InstBuilder::genVoidFunCallInst("classInit", args1));
    }

    {
        list<ValueInst*> args1;
        if (!ismethod) {
            args1.push_back(InstBuilder::genLoadFunArgsVar(obj));
        }
        args1.push_back(InstBuilder::genLoadFunArgsVar("sample_rate"));
        block->pushBackInst(InstBuilder::genVoidFunCallInst("instanceInit", args1));
    }

    // Creates function
    return InstBuilder::genVoidFunction(name, args, block, isvirtual);
}

DeclareFunInst* CodeContainer::generateInstanceInit(const string& name, const string& obj, bool ismethod,
                                                    bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }
    args.push_back(InstBuilder::genNamedTyped("sample_rate", Typed::kInt32));

    BlockInst* block = InstBuilder::genBlockInst();
    {
        list<ValueInst*> args1;
        if (!ismethod) {
            args1.push_back(InstBuilder::genLoadFunArgsVar(obj));
        }
        args1.push_back(InstBuilder::genLoadFunArgsVar("sample_rate"));
        block->pushBackInst(InstBuilder::genVoidFunCallInst("instanceConstants", args1));
    }

    {
        list<ValueInst*> args1;
        if (!ismethod) {
            args1.push_back(InstBuilder::genLoadFunArgsVar(obj));
        }
        block->pushBackInst(InstBuilder::genVoidFunCallInst("instanceResetUserInterface", args1));
    }

    {
        list<ValueInst*> args1;
        if (!ismethod) {
            args1.push_back(InstBuilder::genLoadFunArgsVar(obj));
        }
        block->pushBackInst(InstBuilder::genVoidFunCallInst("instanceClear", args1));
    }

    // Creates function
    return InstBuilder::genVoidFunction(name, args, block, isvirtual);
}

DeclareFunInst* CodeContainer::generateGetSampleRate(const string& name, const string& obj, bool ismethod,
                                                     bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }

    BlockInst* block = InstBuilder::genBlockInst();
    block->pushBackInst(InstBuilder::genRetInst(InstBuilder::genLoadStructVar("fSampleRate")));

    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genInt32Typed(),
                                                  (isvirtual) ? FunTyped::kVirtual : FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* CodeContainer::generateComputeFun(const string& name, const string& obj, bool ismethod, bool isvirtual)
{
    list<NamedTyped*> args;
    if (!ismethod) {
        args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));
    }
    args.push_back(InstBuilder::genNamedTyped("count", Typed::kInt32));
    args.push_back(InstBuilder::genNamedTyped("inputs", Typed::kFloatMacro_ptr_ptr));
    args.push_back(InstBuilder::genNamedTyped("outputs", Typed::kFloatMacro_ptr_ptr));

    // Generates control + DSP block
    BlockInst* block = generateComputeAux();

    // Explicit return
    block->pushBackInst(InstBuilder::genRetInst());

    // Creates function
    return InstBuilder::genVoidFunction(name, args, block, isvirtual);
}

// Memory

DeclareFunInst* CodeContainer::generateCalloc()
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped("count", Typed::kInt64));
    args.push_back(InstBuilder::genNamedTyped("size", Typed::kInt64));

    // Creates function
    FunTyped* fun_type =
        InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid_ptr), FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst("calloc", fun_type);
}

DeclareFunInst* CodeContainer::generateFree()
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped("ptr", Typed::kVoid_ptr));

    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid), FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst("free", fun_type);
}

DeclareFunInst* CodeContainer::generateNewDsp(const string& name, int size)
{
    list<NamedTyped*> args;

    BlockInst* block = InstBuilder::genBlockInst();
    {
        list<ValueInst*> args1;
        args1.push_back(InstBuilder::genInt64NumInst(1));
        args1.push_back(InstBuilder::genInt64NumInst(size));
        block->pushBackInst(InstBuilder::genRetInst(InstBuilder::genCastInst(
            InstBuilder::genFunCallInst("calloc", args1), InstBuilder::genBasicTyped(Typed::kObj_ptr))));
    }

    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kObj_ptr), FunTyped::kLocal);
    return InstBuilder::genDeclareFunInst(name, fun_type, block);
}

DeclareFunInst* CodeContainer::generateDeleteDsp(const string& name, const string& obj)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(obj, Typed::kObj_ptr));

    BlockInst* block = InstBuilder::genBlockInst();
    {
        list<ValueInst*> args1;
        args1.push_back(InstBuilder::genCastInst(InstBuilder::genLoadFunArgsVar(obj),
                                                InstBuilder::genBasicTyped(Typed::kVoid_ptr)));
        block->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("free", args1)));
    }

    // Explicit return
    block->pushBackInst(InstBuilder::genRetInst());

    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid), FunTyped::kLocal);
    return InstBuilder::genDeclareFunInst(name, fun_type, block);
}
