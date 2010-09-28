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
using namespace std;

#include <string>
#include <list>
#include <set>
#include <map>
#include <vector>

#include "code_container.hh"
#include "fir_instructions.hh"
#include "floats.hh"

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
    fGlobalDeclarationInstructions(InstBuilder::genBlockInst()),
    fDeclarationInstructions(InstBuilder::genBlockInst()),
    fInitInstructions(InstBuilder::genBlockInst()),
    fDestroyInstructions(InstBuilder::genBlockInst()),
    fStaticInitInstructions(InstBuilder::genBlockInst()),
    fComputeBlockInstructions(InstBuilder::genBlockInst()),
    fComputeThreadBlockInstructions(InstBuilder::genBlockInst()),
    fComputeFunctions(InstBuilder::genBlockInst()),
    fUserInterfaceInstructions(InstBuilder::genBlockInst())
{
    fCurLoop = new CodeLoop(0);
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
void CodeContainer::openLoop(int size)
{
    fCurLoop = new CodeLoop(fCurLoop, size);
}

/**
 * Open a recursive loop on top of the stack of open loops.
 * @param recsymbol the recursive symbol defined in this loop
 * @param size the number of iterations of the loop
 */
void CodeContainer::openLoop(Tree recsymbol, int size)
{
     fCurLoop = new CodeLoop(recsymbol, fCurLoop, size);
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

inline bool isElement(const set<CodeLoop*>& S, CodeLoop* l)
{
	return S.find(l) != S.end();
}

void CodeContainer::computeForwardDAG(lclgraph dag)
{
    int loop_num = START_TASK_MAX;  // First index to be used for remaining tasks
    
    // Compute forward dependencies
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

void CodeContainer::generateLocalInputs(BlockInst* loop_code)
{
    // Generates line like: FAUSTFLOAT* input0 = &input0_ptr[index];
    for (int index = 0; index < inputs(); index++) {
        string name1 = subst("fInput$0", T(index));
        string name2 = subst("fInput$0_ptr", T(index));
        
        loop_code->pushBackInst(
            InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(name1, Address::kStruct),    
                InstBuilder::genLoadVarAddressInst(
                    InstBuilder::genIndexedAddress(
                        InstBuilder::genNamedAddress(name2, Address::kStruct), InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("index", Address::kLoop))))));
    }
}

void CodeContainer::generateLocalOutputs(BlockInst* loop_code)
{
    // Generates line like: FAUSTFLOAT* ouput0 = &ouput0_ptr[index];
    for (int index = 0; index < outputs(); index++) {
        string name1 = subst("fOutput$0", T(index));
        string name2 = subst("fOutput$0_ptr", T(index));
        
        loop_code->pushBackInst(
            InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(name1, Address::kStruct),  
                InstBuilder::genLoadVarAddressInst(
                    InstBuilder::genIndexedAddress(
                        InstBuilder::genNamedAddress(name2, Address::kStruct), InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("index", Address::kLoop))))));
    }
}

void CodeContainer::generateLoopNode(CodeLoop* loop, BlockInst* loop_code, int loop_num)
{
    if (gFunTaskSwitch) {
        BlockInst* block = InstBuilder::genBlockInst();
        loop->generateVecLoop(block);
        /*
        if (loop->fIsRecursive)
            loop->generateVecLoop(block);
        else
            loop->generateVectorizedLoop(block, 4);
        */
        Loop2FunctionBuider builder(subst("fun$0", T(loop_num)), block, gDSPStruct);
        fComputeFunctions->pushBackInst(builder.fFunctionDef);
        loop_code->pushBackInst(InstBuilder::genLabelInst((loop->fIsRecursive) ? subst("// Recursive function $0", T(loop_num)) : subst("// Vectorizable function $0", T(loop_num))));
        loop_code->pushBackInst(builder.fFunctionCall);
    } else {
        loop_code->pushBackInst(InstBuilder::genLabelInst((loop->fIsRecursive) ? subst("// Recursive loop $0", T(loop_num)) : subst("// Vectorizable loop $0", T(loop_num))));
        /*
        if (loop->fIsRecursive)
            loop->generateVecLoop(loop_code);
        else
            loop->generateVectorizedLoop(loop_code, 4);
        */
        loop->generateVecLoop(loop_code);
    }
}

void CodeContainer::generateParLoopNode(CodeLoop* loop, BlockInst* loop_code, int loop_num)
{
    if (gFunTaskSwitch) {
        BlockInst* block = InstBuilder::genBlockInst();
        loop->generateVecLoop1(block);
        Loop2FunctionBuider builder(subst("fun$0", T(loop_num)), block, gDSPStruct);
        fComputeFunctions->pushBackInst(builder.fFunctionDef);
        loop_code->pushBackInst(InstBuilder::genLabelInst((loop->fIsRecursive) ? subst("// Recursive function $0", T(loop_num)) : subst("// Vectorisable function $0", T(loop_num))));
        loop_code->pushBackInst(builder.fFunctionCall);
    } else {
        loop_code->pushBackInst(InstBuilder::genLabelInst((loop->fIsRecursive) ? subst("// Recursive loop $0", T(loop_num)) : subst("// Vectorisable loop $0", T(loop_num))));
        loop->generateVecLoop1(loop_code);
    }
}

void CodeContainer::generateLoopDAG(BlockInst* block)
{
    int loop_num = 0;
    
    if (gDeepFirstSwitch) {
        set<CodeLoop*> visited;
        list<CodeLoop*> result;
        generateLoopDeepFirst(fCurLoop, visited, result);
        for (list<CodeLoop*>::const_iterator p = result.begin(); p != result.end(); p++) {
            generateLoopNode(*p, block, loop_num++);
        }
    } else {
        lclgraph G;
        CodeLoop::sortGraph(fCurLoop, G);
        for (int l = G.size() - 1; l >= 0; l--) {
            for (lclset::const_iterator p = G[l].begin(); p != G[l].end(); p++) {
                generateLoopNode(*p, block, loop_num++);
            }
        }
    }
}

void CodeContainer::generateLoopDeepFirst(CodeLoop* l, set<CodeLoop*>& visited, list<CodeLoop*>& result)
{
	// Avoid printing already printed loops
	if (isElement(visited, l)) return;
	
	// Remember we have printed this loop
	visited.insert(l);
	
	// Compute the dependencies loops (that need to be computed before this one)
	for (lclset::const_iterator p = l->fBackwardLoopDependencies.begin(); p != l->fBackwardLoopDependencies.end(); p++) {
        generateLoopDeepFirst(*p, visited, result);
    }
    
    // Keep the non-empty loops in result
    if (!l->isEmpty())
        result.push_back(l);
}

StatementInst* CodeContainer::generateDAGLoopVariant0()
{
    string index = "index";
    
    // Define result block
    BlockInst* block_res = InstBuilder::genBlockInst();
    
    // Declare the "index" variable outside the loop
    DeclareVarInst* index_dec = InstBuilder::genDeclareVarInst(index, InstBuilder::genBasicTyped(Typed::kInt), Address::kStack);
    block_res->pushBackInst(index_dec);
    block_res->pushBackInst(InstBuilder::genLabelInst("// Main loop"));
   
    BlockInst* loop_code = InstBuilder::genBlockInst();
    
    // Generate local input/output access
    generateLocalInputs(loop_code);
    generateLocalOutputs(loop_code);
     
    // Generate : int count = 32;
    DeclareVarInst* count_dec1 = InstBuilder::genDeclareVarInst("count", InstBuilder::genBasicTyped(Typed::kInt), Address::kStack, InstBuilder::genIntNumInst(gVecSize));
    loop_code->pushBackInst(count_dec1);
    
    // Generates the loop DAG
    generateLoopDAG(loop_code);
      
    // Generates the DAG enclosing loop
    StoreVarInst* loop_init = InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(index, Address::kStack), InstBuilder::genIntNumInst(0));
    
    ValueInst* loop_end = InstBuilder::genBinopInst(kLE, 
                            InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kStack)),
                            InstBuilder::genBinopInst(kSub,
                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fullcount", Address::kFunArgs)),
                                InstBuilder::genIntNumInst(gVecSize)));
    StoreVarInst* loop_increment = InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(index, Address::kLoop),
                        InstBuilder::genBinopInst(kAdd, 
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                    InstBuilder::genIntNumInst(gVecSize)));

    StatementInst* loop = InstBuilder::genForLoopInst(loop_init, loop_end, loop_increment, loop_code);
    
    // Put loop in block_res
    block_res->pushBackInst(loop);
    
    // Remaining frames
    block_res->pushBackInst(InstBuilder::genLabelInst("// Remaining frames"));
    
    ValueInst* if_cond = InstBuilder::genBinopInst(kLT, 
                            InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kStack)),
                            InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fullcount", Address::kFunArgs)));
   
    BlockInst* then_cond = InstBuilder::genBlockInst();
     
    // Generate local input/output access
    generateLocalInputs(then_cond);
    generateLocalOutputs(then_cond);
   
    // Generate : int count = fullcount-index;
    DeclareVarInst* count_dec2 = 
        InstBuilder::genDeclareVarInst("count", InstBuilder::genBasicTyped(Typed::kInt), Address::kStack, 
            InstBuilder::genBinopInst(kSub,
                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fullcount", Address::kFunArgs)),
                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kStack))));
                
    then_cond->pushBackInst(count_dec2);
    
    // Generates the loop DAG
    generateLoopDAG(then_cond);
    
    block_res->pushBackInst(InstBuilder::genIfInst(if_cond, then_cond));
    return block_res;
}

StatementInst* CodeContainer::generateDAGLoopVariant1()
{
    BlockInst* loop_code = InstBuilder::genBlockInst();
    
    // Generate local input/output access
    generateLocalInputs(loop_code);
    generateLocalOutputs(loop_code);
        
    // Generate : int count = min(32, (fullcount - index)) 
    ValueInst* init1 = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fullcount", Address::kFunArgs));
    ValueInst* init2 = InstBuilder::genBinopInst(kSub, init1, InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("index", Address::kLoop)));
    list<ValueInst*> min_fun_args;
    min_fun_args.push_back(InstBuilder::genIntNumInst(gVecSize));
    min_fun_args.push_back(init2);
    ValueInst* init3 = InstBuilder::genFunCallInst("min", min_fun_args);
    StatementInst* count_dec = InstBuilder::genDeclareVarInst("count", InstBuilder::genBasicTyped(Typed::kInt), Address::kStack, init3);
    loop_code->pushBackInst(count_dec);
    
    // Generates the loop DAG
    generateLoopDAG(loop_code);
        
    // Generates the DAG enclosing loop
    string index = "index";
    DeclareVarInst* loop_init = InstBuilder::genDeclareVarInst(index, InstBuilder::genBasicTyped(Typed::kInt), Address::kLoop, InstBuilder::genIntNumInst(0));
    
    ValueInst* loop_end = InstBuilder::genBinopInst(kLT, 
                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fullcount", Address::kFunArgs)));
    StoreVarInst* loop_increment = InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(index, Address::kLoop),
                        InstBuilder::genBinopInst(kAdd, 
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                    InstBuilder::genIntNumInst(gVecSize)));

    StatementInst* loop = InstBuilder::genForLoopInst(loop_init, loop_end, loop_increment, loop_code);
    return loop;
}

// LabelInst are used to add OMP directive in the code 
StatementInst* CodeContainer::generateDAGLoopOMP()
{
    BlockInst* result_code = InstBuilder::genBlockInst();
    
    // Analysis to discover which stack variables have to be used in the "firstprivate" list
    struct StackVarAnalyser : public DispatchVisitor {

        list<string> fFirstPrivateTable;

        virtual void visit(DeclareVarInst* inst) 
        { 
            DispatchVisitor::visit(inst);
            ArrayTyped* array_typed;
            
            // Keep "simple" stack variables and pointers on simple variables (that is everything but arrays)
            if (inst->fAccess == Address::kStack && !((array_typed = dynamic_cast<ArrayTyped*>(inst->fTyped)) && array_typed->fSize > 0)) {
                fFirstPrivateTable.push_back(inst->fName);
            }
        }
    };
    
    // Setup "firstprivate" list
    StackVarAnalyser analyser;
    fComputeBlockInstructions->accept(&analyser);
    
    if (analyser.fFirstPrivateTable.size() == 0) {
        result_code->pushBackInst(InstBuilder::genLabelInst("#pragma omp parallel"));
    } else {
        std::ostringstream firstprivate; firstprivate << "\t" << "firstprivate(";
        list<string>::const_iterator it1;
        for (it1 = analyser.fFirstPrivateTable.begin(); it1 != analyser.fFirstPrivateTable.end(); it1++) {
            firstprivate << (*it1);
            if (++it1 != analyser.fFirstPrivateTable.end()) firstprivate<< ", "; 
            it1--;
        }
        firstprivate << ")";
        result_code->pushBackInst(InstBuilder::genLabelInst("#pragma omp parallel\\"));
        result_code->pushBackInst(InstBuilder::genLabelInst(firstprivate.str()));
    }
     
    BlockInst* parallel_code = InstBuilder::genBlockInst();
    parallel_code->setIndent(true);
    
    BlockInst* loop_code = InstBuilder::genBlockInst();
    
    // Generate local input/output access
    generateLocalInputs(loop_code);
    generateLocalOutputs(loop_code);
    
    // Generate : int count = min(32, (fullcount - index)) 
    ValueInst* init1 = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fullcount", Address::kFunArgs));
    ValueInst* init2 = InstBuilder::genBinopInst(kSub, init1, InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("index", Address::kLoop)));
    list<ValueInst*> min_fun_args;
    min_fun_args.push_back(InstBuilder::genIntNumInst(gVecSize));
    min_fun_args.push_back(init2);
    ValueInst* init3 = InstBuilder::genFunCallInst("min", min_fun_args);
    StatementInst* count_dec = InstBuilder::genDeclareVarInst("count", InstBuilder::genBasicTyped(Typed::kInt), Address::kStack, init3);
    loop_code->pushBackInst(count_dec);
    
    // Generates the loop DAG
    lclgraph G;
    CodeLoop::sortGraph(fCurLoop, G);
    int loop_num = 0;
    bool is_single = false; // Generates "#pragma omp single" once when we stay if a sequence of "single" loops
    
    for (int l = G.size() - 1; l >= 0; l--) {
        BlockInst* omp_sections_block = InstBuilder::genBlockInst();
        if (G[l].size() > 1) {
            loop_code->pushBackInst(InstBuilder::genLabelInst("#pragma omp sections"));
            omp_sections_block->setIndent(true);
        }
        for (lclset::const_iterator p = G[l].begin(); p != G[l].end(); p++) {
            BlockInst* omp_section_block = InstBuilder::genBlockInst();
            if (G[l].size() == 1) { // Only one loop
                if (!(*p)->fIsRecursive && gOpenMPLoop) {
                    generateParLoopNode(*p, omp_section_block, loop_num++);
                } else {
                    omp_section_block->setIndent(true);
                    if (!is_single) {
                        omp_sections_block->pushBackInst(InstBuilder::genLabelInst("#pragma omp single"));
                        is_single = true;
                    } else {
                        omp_sections_block->pushBackInst(InstBuilder::genLabelInst("// Still in a single section"));
                    }
                    generateLoopNode(*p, omp_section_block, loop_num++);
                }
            } else {
                is_single = false;
                omp_section_block->setIndent(true);
                omp_sections_block->pushBackInst(InstBuilder::genLabelInst("#pragma omp section"));
                generateLoopNode(*p, omp_section_block, loop_num++);
            }
            omp_sections_block->pushBackInst(omp_section_block);
        }
        loop_code->pushBackInst(omp_sections_block);
    }
    
    // Generates the DAG enclosing loop
    string index = "index";
    DeclareVarInst* loop_init = InstBuilder::genDeclareVarInst(index, InstBuilder::genBasicTyped(Typed::kInt), Address::kLoop, InstBuilder::genIntNumInst(0));
    
    ValueInst* loop_end = InstBuilder::genBinopInst(kLT, 
                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fullcount", Address::kFunArgs)));
    StoreVarInst* loop_increment = InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(index, Address::kLoop),
                        InstBuilder::genBinopInst(kAdd, 
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                    InstBuilder::genIntNumInst(gVecSize)));

  
    StatementInst* loop = InstBuilder::genForLoopInst(loop_init, loop_end, loop_increment, loop_code);
    
    parallel_code->pushBackInst(loop);
    result_code->pushBackInst(parallel_code);
    return result_code;
}

void CodeContainer::generateDAGLoopWSSAux1(lclgraph dag, BlockInst* loop_code, bool master_thread)
{
    // Compute ready tasks list
    vector<int> task_num;
    for (int l = dag.size() - 1; l >= 0; l--) {
        lclset::const_iterator next;
        for (lclset::const_iterator p = dag[l].begin(); p != dag[l].end(); p++) {
            if ((*p)->fBackwardLoopDependencies.size() == 0) {
                task_num.push_back((*p)->fIndex);
            }
        }
    }
    
    BlockInst* gen_code;
    BlockInst* then_block;
    
    if (master_thread) {
        then_block = InstBuilder::genBlockInst();
        gen_code = then_block;
    } else {
        gen_code = loop_code;
    }
    
    // Last stage connected to end task
    if (dag[0].size() > 1) {
        list<ValueInst*> fun_args;
        fun_args.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fTaskGraph", Address::kStruct)));
        fun_args.push_back(InstBuilder::genIntNumInst(LAST_TASK_INDEX));
        fun_args.push_back(InstBuilder::genIntNumInst(dag[0].size()));
        gen_code->pushBackInst(InstBuilder::genLabelInst("// Initialize end task, if more than one input"));
        gen_code->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("initTask", fun_args)));
    } else {
        gen_code->pushBackInst(InstBuilder::genLabelInst("// End task has only one input, so will be directly activated"));
    }
    
    // Compute init section
    gen_code->pushBackInst(InstBuilder::genLabelInst("// Only initialize tasks with more than one input"));
    for (int l = dag.size() - 1; l >= 0; l--) {
        for (lclset::const_iterator p = dag[l].begin(); p != dag[l].end(); p++) {
            if ((*p)->fBackwardLoopDependencies.size() > 1)  { // Only initialize taks with more than 1 input, since taks with one input are "directly" activated.
                list<ValueInst*> fun_args;
                fun_args.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fTaskGraph", Address::kStruct)));
                fun_args.push_back(InstBuilder::genIntNumInst((*p)->fIndex));
                fun_args.push_back(InstBuilder::genIntNumInst((*p)->fBackwardLoopDependencies.size()));
                gen_code->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("initTask", fun_args)));
            }
        }
    }

    // Push n - 1 ready tasks                                                        
    for (int i = 0; i < task_num.size() - 1; i++) {
        list<ValueInst*> fun_args;
        fun_args.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("taskqueue", Address::kStack)));
        fun_args.push_back(InstBuilder::genIntNumInst(task_num[i]));
        gen_code->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("pushHead", fun_args)));
    }
        
    gen_code->pushBackInst(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress("tasknum", Address::kStack), InstBuilder::genIntNumInst(task_num[task_num.size() - 1])));
    
    if (master_thread) {
        loop_code->pushBackInst(InstBuilder::genLabelInst("// Master thread init processing"));
        ValueInst* if_cond = InstBuilder::genBinopInst(kEQ, InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("num_thread", Address::kFunArgs)), InstBuilder::genIntNumInst(0));
        loop_code->pushBackInst(InstBuilder::genIfInst(if_cond, then_block));
    }   
}

void CodeContainer::generateDAGLoopWSSAux2(BlockInst* loop_code, bool obj)
{
    loop_code->pushBackInst(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress("fFullcount", Address::kStruct),
        InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fullcount", Address::kFunArgs))));
    loop_code->pushBackInst(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress("fIndex", Address::kStruct),
        InstBuilder::genIntNumInst(0)));
        
    list<ValueInst*> fun_args0;
    loop_code->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("GetRealTime", fun_args0)));
    
    list<ValueInst*> fun_args3;
    fun_args3.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fDynamicNumThreads", Address::kStruct)));
    loop_code->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("initAllTaskQueue", fun_args3)));
    
    list<NamedTyped*> callback_args;
    callback_args.push_back(InstBuilder::genNamedTyped("dsp", InstBuilder::genBasicTyped(Typed::kVoid_ptr)));
    callback_args.push_back(InstBuilder::genNamedTyped("cur_thread", InstBuilder::genBasicTyped(Typed::kInt)));
      
    list<ValueInst*> fun_args1;
    fun_args1.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fThreadPool", Address::kStruct)));
    fun_args1.push_back(InstBuilder::genBinopInst(kSub, InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fDynamicNumThreads", Address::kStruct)), InstBuilder::genIntNumInst(1)));
     
    if (obj)
        fun_args1.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("dsp", Address::kFunArgs)));
    else 
        fun_args1.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("this", Address::kFunArgs)));
    loop_code->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("signalAll", fun_args1)));

    list<ValueInst*> fun_args2;
    if (obj)
        fun_args2.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("dsp", Address::kFunArgs)));
    fun_args2.push_back(InstBuilder::genIntNumInst(0));
    loop_code->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("computeThread", fun_args2)));
}

void CodeContainer::generateDAGLoopWSSAux3()
{
    // Needed in the struct
    pushDeclare(InstBuilder::genDeclareVarInst("fIndex", InstBuilder::genBasicTyped(Typed::kInt), (Address::AccessType)(Address::kStruct|Address::kVolatile))); 
    pushDeclare(InstBuilder::genDeclareVarInst("fFullcount", InstBuilder::genBasicTyped(Typed::kInt), Address::kStruct)); 
    pushDeclare(InstBuilder::genDeclareVarInst("fStaticNumThreads", InstBuilder::genBasicTyped(Typed::kInt), Address::kStruct)); 
    pushDeclare(InstBuilder::genDeclareVarInst("fDynamicNumThreads", InstBuilder::genBasicTyped(Typed::kInt), Address::kStruct)); 
    pushDeclare(InstBuilder::genDeclareVarInst("fThreadPool", InstBuilder::genBasicTyped(Typed::kVoid_ptr), Address::kStruct)); 
    pushDeclare(InstBuilder::genDeclareVarInst("fTaskGraph", InstBuilder::genBasicTyped(Typed::kVoid_ptr), Address::kStruct)); 
    pushDeclare(InstBuilder::genDeclareVarInst("fTaskQueueTable", InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(Typed::kVoid_ptr), 16), Address::kStruct)); 
    
    // Scheduler prototypes declaration
    pushGlobalDeclare(InstBuilder::genLabelInst("#ifdef __cplusplus"));
    pushGlobalDeclare(InstBuilder::genLabelInst("extern \"C\""));
    pushGlobalDeclare(InstBuilder::genLabelInst("{"));
    pushGlobalDeclare(InstBuilder::genLabelInst("#endif"));
    
    createVoidFunction("GetRealTime");
    
    createFunction0("createThreadPool", Typed::kVoid_ptr);
    createFunction1("deleteThreadPool", Typed::kVoid, "pool", Typed::kVoid_ptr);
    createFunction2("startAll", Typed::kVoid, "pool", Typed::kVoid_ptr, "num_threads", Typed::kInt);
    createFunction3("signalAll", Typed::kVoid, "pool", Typed::kVoid_ptr, "num_threads", Typed::kInt, "dsp", Typed::kVoid_ptr);
    
    createVoidFunction("initTaskQueue");
    createFunction1("initAllTaskQueue", Typed::kVoid, "num_threads", Typed::kInt);
    createFunction1("createTaskQueue", Typed::kVoid_ptr, "cur_thread", Typed::kInt);
    createFunction1("deleteTaskQueue", Typed::kVoid, "queue", Typed::kVoid_ptr);
    createFunction2("pushHead", Typed::kVoid, "queue", Typed::kVoid_ptr, "task", Typed::kInt);
    createFunction1("popHead", Typed::kInt, "queue", Typed::kVoid_ptr);
    createFunction2("getNextTask", Typed::kInt, "cur_thread", Typed::kInt, "dynamic_threads", Typed::kInt);
    
    createFunction0("createTaskGraph", Typed::kVoid_ptr);
    createFunction1("deleteTaskGraph", Typed::kVoid, "graph", Typed::kVoid_ptr);
    createFunction3("initTask", Typed::kVoid, "graph", Typed::kVoid_ptr, "task", Typed::kInt, "count", Typed::kInt);
    createFunction4("activateOutputTask1", Typed::kVoid, "graph", Typed::kVoid_ptr, "queue", Typed::kVoid_ptr, "task", Typed::kInt, "tasknum", Typed::kInt_ptr);
    createFunction3("activateOutputTask2", Typed::kVoid, "graph", Typed::kVoid_ptr, "queue", Typed::kVoid_ptr, "task", Typed::kInt);
    createFunction4("activateOneOutputTask", Typed::kVoid, "graph", Typed::kVoid_ptr, "queue", Typed::kVoid_ptr, "task", Typed::kInt, "tasknum", Typed::kInt_ptr);
    createFunction3("getReadyTask", Typed::kVoid, "graph", Typed::kVoid_ptr, "queue", Typed::kVoid_ptr, "tasknum", Typed::kInt_ptr);
    
    createFunction0("getStaticThreadsNum", Typed::kInt);
    createFunction0("getDynamicThreadsNum", Typed::kInt);
    
    pushGlobalDeclare(InstBuilder::genLabelInst("#ifdef __cplusplus"));
    pushGlobalDeclare(InstBuilder::genLabelInst("}"));
    pushGlobalDeclare(InstBuilder::genLabelInst("#endif"));
    
    // Specific init instructions
    list<ValueInst*> fun_args;
    pushInitMethod(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress("fStaticNumThreads", Address::kStruct),
        InstBuilder::genFunCallInst("getStaticThreadsNum", fun_args)));
     pushInitMethod(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress("fDynamicNumThreads", Address::kStruct),
        InstBuilder::genFunCallInst("getDynamicThreadsNum", fun_args)));
    pushInitMethod(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress("fThreadPool", Address::kStruct),
        InstBuilder::genFunCallInst("createThreadPool", fun_args)));
    pushInitMethod(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress("fTaskGraph", Address::kStruct),
        InstBuilder::genFunCallInst("createTaskGraph", fun_args)));
    
    pushInitMethod(InstBuilder::genDropInst(InstBuilder::genFunCallInst("initTaskQueue", fun_args)));
     
    StatementInst* init_loop1 = InstBuilder::genDeclareVarInst("i", InstBuilder::genBasicTyped(Typed::kInt), Address::kLoop, InstBuilder::genIntNumInst(0));
    ValueInst* end_loop1 = InstBuilder::genBinopInst(kLT, InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("i", Address::kLoop)), InstBuilder::genIntNumInst(16));
    StoreVarInst* inc_loop1 = InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress("i", Address::kLoop),
                        InstBuilder::genBinopInst(kAdd, 
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("i", Address::kLoop)),
                                    InstBuilder::genIntNumInst(1)));
  
    list<StatementInst*> code1;
    list<ValueInst*> fun_args1;
    fun_args1.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("i", Address::kLoop)));
    code1.push_back(InstBuilder::genStoreVarInst(InstBuilder::genIndexedAddress(InstBuilder::genNamedAddress("fTaskQueueTable", Address::kStruct), 
        InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("i", Address::kLoop))), 
        InstBuilder::genFunCallInst("createTaskQueue", fun_args1)));
        
    pushInitMethod(InstBuilder::genForLoopInst(init_loop1, end_loop1, inc_loop1, InstBuilder::genBlockInst(code1)));
    
    list<ValueInst*> fun_args2;
    fun_args2.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fThreadPool", Address::kStruct)));
    fun_args2.push_back(InstBuilder::genBinopInst(kSub, InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fStaticNumThreads", Address::kStruct)), InstBuilder::genIntNumInst(1)));
    pushInitMethod(InstBuilder::genDropInst(InstBuilder::genFunCallInst("startAll", fun_args2)));
  
    // Specific destroy instructions
    list<ValueInst*> fun_args3;
    fun_args3.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fThreadPool", Address::kStruct)));
    pushDestroyMethod(InstBuilder::genDropInst(InstBuilder::genFunCallInst("deleteThreadPool", fun_args3)));
    list<ValueInst*> fun_args4;
    fun_args4.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fTaskGraph", Address::kStruct)));
    pushDestroyMethod(InstBuilder::genDropInst(InstBuilder::genFunCallInst("deleteTaskGraph", fun_args4)));
    
    StatementInst* init_loop2 = InstBuilder::genDeclareVarInst("i", InstBuilder::genBasicTyped(Typed::kInt), Address::kLoop, InstBuilder::genIntNumInst(0));
    ValueInst* end_loop2 = InstBuilder::genBinopInst(kLT, InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("i", Address::kLoop)), InstBuilder::genIntNumInst(16));
    StoreVarInst* inc_loop2 = InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress("i", Address::kLoop),
                        InstBuilder::genBinopInst(kAdd, 
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("i", Address::kLoop)),
                                    InstBuilder::genIntNumInst(1)));

    list<StatementInst*> code2;
    list<ValueInst*> fun_args5;
    fun_args5.push_back(InstBuilder::genLoadVarInst(InstBuilder::genIndexedAddress(InstBuilder::genNamedAddress("fTaskQueueTable", Address::kStruct),
                                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("i", Address::kLoop)))));
    code2.push_back(InstBuilder::genDropInst(InstBuilder::genFunCallInst("deleteTaskQueue", fun_args5)));
    pushDestroyMethod(InstBuilder::genForLoopInst(init_loop2, end_loop2, inc_loop2, InstBuilder::genBlockInst(code2)));
}

StatementInst* CodeContainer::generateDAGLoopWSS(lclgraph dag)
{
    BlockInst* loop_code = fComputeThreadBlockInstructions;
    loop_code->pushBackInst(InstBuilder::genDeclareVarInst("tasknum", InstBuilder::genBasicTyped(Typed::kInt), Address::kStack, InstBuilder::genIntNumInst(WORK_STEALING_INDEX)));
    
    ValueInst* switch_cond = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("tasknum", Address::kStack));
    SwitchInst* switch_block = InstBuilder::genSwitchInst(switch_cond);
      
    // Generate input/output access
    // Generates line like: fInput0 = &fInput0_ptr[index];
    for (int index = 0; index < inputs(); index++) {
        string name1 = subst("fInput$0", T(index));
        string name2 = subst("fInput$0_ptr", T(index));
        
        loop_code->pushBackInst(
            InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(name1, Address::kStruct),
                InstBuilder::genLoadVarAddressInst(
                    InstBuilder::genIndexedAddress(
                        InstBuilder::genNamedAddress(name2, Address::kStruct), InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fIndex", (Address::AccessType)(Address::kStruct|Address::kVolatile)))))));
    }

    // Generates line like: fOutput0 = &fOutput0_ptr[index];
    for (int index = 0; index < outputs(); index++) {
        string name1 = subst("fOutput$0", T(index));
        string name2 = subst("fOutput$0_ptr", T(index));
        
        loop_code->pushBackInst(
            InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(name1, Address::kStruct), 
                InstBuilder::genLoadVarAddressInst(
                    InstBuilder::genIndexedAddress(
                        InstBuilder::genNamedAddress(name2, Address::kStruct), InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fIndex", (Address::AccessType)(Address::kStruct|Address::kVolatile)))))));
    }
    
    loop_code->pushBackInst(InstBuilder::genDeclareVarInst("taskqueue", 
        InstBuilder::genBasicTyped(Typed::kVoid_ptr), 
        Address::kStack,
        InstBuilder::genLoadVarInst(InstBuilder::genIndexedAddress(InstBuilder::genNamedAddress("fTaskQueueTable", Address::kStruct),  
            InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("num_thread", Address::kFunArgs))))));
    
    list<ValueInst*> fun_args;
    fun_args.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("taskqueue", Address::kStack)));
         
    generateDAGLoopWSSAux1(dag, loop_code, true);
          
    // Work stealing task
    BlockInst* ws_block = InstBuilder::genBlockInst();
    ws_block->pushBackInst(InstBuilder::genLabelInst("// Work Stealing task"));
    list<ValueInst*> fun_args2;
    fun_args2.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("num_thread", Address::kFunArgs)));
    fun_args2.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fDynamicNumThreads", Address::kStruct)));
    ws_block->pushBackInst(InstBuilder::genStoreVarInst(
        InstBuilder::genNamedAddress("tasknum", Address::kStack), 
        InstBuilder::genFunCallInst("getNextTask", fun_args2)));
    switch_block->addCase(WORK_STEALING_INDEX, ws_block);
    
    // Last task
    BlockInst* last_block = InstBuilder::genBlockInst();
    last_block->pushBackInst(InstBuilder::genLabelInst("// Last task"));
    last_block->pushBackInst(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress("fIndex", (Address::AccessType)(Address::kStruct|Address::kVolatile)),
                                InstBuilder::genBinopInst(kAdd, 
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fIndex", (Address::AccessType)(Address::kStruct|Address::kVolatile))),
                                    InstBuilder::genIntNumInst(gVecSize))));
                                    
    // Generates line like: fInput0 = &fInput0_ptr[index];
    for (int index = 0; index < inputs(); index++) {
        string name1 = subst("fInput$0", T(index));
        string name2 = subst("fInput$0_ptr", T(index));
        
        last_block->pushBackInst(
            InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(name1, Address::kStruct),  
                InstBuilder::genLoadVarAddressInst(
                    InstBuilder::genIndexedAddress(
                        InstBuilder::genNamedAddress(name2, Address::kStruct), 
                            InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fIndex", (Address::AccessType)(Address::kStruct|Address::kVolatile)))))));
    }

    // Generates line like: fOutput0 = &fOuput0_ptr[index];
    for (int index = 0; index < outputs(); index++) {
        string name1 = subst("fOutput$0", T(index));
        string name2 = subst("fOutput$0_ptr", T(index));
        
        last_block->pushBackInst(
            InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(name1, Address::kStruct),  
                InstBuilder::genLoadVarAddressInst(
                    InstBuilder::genIndexedAddress(
                        InstBuilder::genNamedAddress(name2, Address::kStruct), 
                            InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fIndex", (Address::AccessType)(Address::kStruct|Address::kVolatile)))))));
    }
    
    // Generates init DAG and ready tasks activations                                
    generateDAGLoopWSSAux1(dag, last_block, false);
    switch_block->addCase(LAST_TASK_INDEX, last_block);
  
    // Generates global "switch/case"
    int loop_num = START_TASK_MAX;  // First index to be used for remaining tasks
    
    ValueInst* while_cond = InstBuilder::genBinopInst(kLT, 
        InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fIndex", (Address::AccessType)(Address::kStruct|Address::kVolatile))),
        InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fFullcount", Address::kStruct)));
    BlockInst* switch_block_code = InstBuilder::genBlockInst();
    
    // Generates switch/case block "header"
    ValueInst* init1 = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fFullcount", Address::kStruct));
    ValueInst* init2 = InstBuilder::genBinopInst(kSub, init1, InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fIndex", Address::kStruct)));
    list<ValueInst*> min_fun_args;
    min_fun_args.push_back(InstBuilder::genIntNumInst(gVecSize));
    min_fun_args.push_back(init2);
    ValueInst* init3 = InstBuilder::genFunCallInst("min", min_fun_args);
    StatementInst* count_dec = InstBuilder::genDeclareVarInst("count", InstBuilder::genBasicTyped(Typed::kInt), Address::kStack, init3);
    switch_block_code->pushBackInst(count_dec);
    
    for (int l = dag.size() - 1; l > 0; l--) {
        for (lclset::const_iterator p = dag[l].begin(); p != dag[l].end(); p++, loop_num++) {
        
            // Generates a "case" block for each task
            BlockInst* case_block = InstBuilder::genBlockInst();
            generateLoopNode(*p, case_block, loop_num);
            
            // Add output tasks activation code
            
            // One output only
            if ((*p)->fForwardLoopDependencies.size() == 1) {
                
                lclset::const_iterator p1 = (*p)->fForwardLoopDependencies.begin();
                if ((*p1)->fBackwardLoopDependencies.size () == 1) {
                    case_block->pushBackInst(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress("tasknum", Address::kStack), InstBuilder::genIntNumInst((*p1)->fIndex))); 
                } else {
                    list<ValueInst*> fun_args;
                    fun_args.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fTaskGraph", Address::kStruct)));
                    fun_args.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("taskqueue", Address::kStack)));
                    fun_args.push_back(InstBuilder::genIntNumInst((*p1)->fIndex));
                    fun_args.push_back(InstBuilder::genLoadVarAddressInst(InstBuilder::genNamedAddress("tasknum", Address::kStack)));
                    case_block->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("activateOneOutputTask", fun_args)));
                }
                
            } else {
                
                CodeLoop* keep = NULL;
                // Find one output with only one backward dependencies
                for (lclset::const_iterator p1 = (*p)->fForwardLoopDependencies.begin(); p1 != (*p)->fForwardLoopDependencies.end(); p1++) {
                    if ((*p1)->fBackwardLoopDependencies.size () == 1) {
                        keep = *p1;
                        break;
                    }
                }
                
                if (keep == NULL) {
                    case_block->pushBackInst(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress("tasknum", Address::kStack), InstBuilder::genIntNumInst(WORK_STEALING_INDEX))); 
                }                
                
                for (lclset::const_iterator p1 = (*p)->fForwardLoopDependencies.begin(); p1 != (*p)->fForwardLoopDependencies.end(); p1++) {
                    if ((*p1)->fBackwardLoopDependencies.size () == 1) {  // Task is the only input
                        if (*p1 != keep) {
                            list<ValueInst*> fun_args;
                            fun_args.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("taskqueue", Address::kStack)));
                            fun_args.push_back(InstBuilder::genIntNumInst((*p1)->fIndex));
                            case_block->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("pushHead", fun_args)));
                        }
                    } else {
                        if (keep == NULL) {
                            list<ValueInst*> fun_args;
                            fun_args.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fTaskGraph", Address::kStruct)));
                            fun_args.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("taskqueue", Address::kStack)));
                            fun_args.push_back(InstBuilder::genIntNumInst((*p1)->fIndex));
                            fun_args.push_back(InstBuilder::genLoadVarAddressInst(InstBuilder::genNamedAddress("tasknum", Address::kStack)));
                            case_block->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("activateOutputTask1", fun_args)));
                        } else {
                            list<ValueInst*> fun_args;
                            fun_args.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fTaskGraph", Address::kStruct)));
                            fun_args.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("taskqueue", Address::kStack)));
                            fun_args.push_back(InstBuilder::genIntNumInst((*p1)->fIndex));
                            case_block->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("activateOutputTask2", fun_args)));
                        }
                    }
                }
                
                if (keep != NULL) {
                    case_block->pushBackInst(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress("tasknum", Address::kStack), InstBuilder::genIntNumInst(keep->fIndex))); 
                } else {
                    list<ValueInst*> fun_args;
                    fun_args.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fTaskGraph", Address::kStruct)));
                    fun_args.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("taskqueue", Address::kStack)));
                    fun_args.push_back(InstBuilder::genLoadVarAddressInst(InstBuilder::genNamedAddress("tasknum", Address::kStack)));
                    case_block->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("getReadyTask", fun_args)));
                }
            }

            // Add the "case" block
            switch_block->addCase(loop_num, case_block);
        }
    }
    
    // Last stage
    lclset level = dag[0];
            
    if (level.size() == 1) {
        BlockInst* case_block = InstBuilder::genBlockInst();
        generateLoopNode(*level.begin(), case_block, loop_num);
        case_block->pushBackInst(InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress("tasknum", Address::kStack), InstBuilder::genIntNumInst(LAST_TASK_INDEX))); 
        // Add the "case" block
        switch_block->addCase(loop_num, case_block);
    } else {
        for (lclset::const_iterator p = level.begin(); p != level.end(); p++, loop_num++) {
            BlockInst* case_block = InstBuilder::genBlockInst();
            generateLoopNode(*p, case_block, loop_num);
            
            list<ValueInst*> fun_args;
            fun_args.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fTaskGraph", Address::kStruct)));
            fun_args.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("taskqueue", Address::kStack)));
            fun_args.push_back(InstBuilder::genIntNumInst(LAST_TASK_INDEX));
            fun_args.push_back(InstBuilder::genLoadVarAddressInst(InstBuilder::genNamedAddress("tasknum", Address::kStack)));
            case_block->pushBackInst(InstBuilder::genDropInst(InstBuilder::genFunCallInst("activateOneOutputTask", fun_args)));
            // Add the "case" block
            switch_block->addCase(loop_num, case_block);
        }
    }
    
    // Finishes switch block
    switch_block_code->pushBackInst(switch_block);
    WhileLoopInst* while_block = InstBuilder::genWhileLoopInst(while_cond, switch_block_code);
    
    // Add the "while" block
    loop_code->pushBackInst(while_block);
    return loop_code;
}

bool CodeContainer::sortFunction1(StatementInst* a, StatementInst* b) 
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
    return true; 
}

void CodeContainer::createVoidFunction(const string& name)
{
    list<NamedTyped*> args;
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid));
    DeclareFunInst* fun = InstBuilder::genDeclareFunInst(name, fun_type);
    pushGlobalDeclare(fun);
}

void CodeContainer::createFunction0(const string& name, Typed::VarType res)
{
    list<NamedTyped*> args;
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    DeclareFunInst* fun = InstBuilder::genDeclareFunInst(name, fun_type);
    pushGlobalDeclare(fun);
}

void CodeContainer::createFunction1(const string& name, Typed::VarType res, const string& arg1, Typed::VarType arg1_ty)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(arg1, InstBuilder::genBasicTyped(arg1_ty)));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    DeclareFunInst* fun = InstBuilder::genDeclareFunInst(name, fun_type);
    pushGlobalDeclare(fun);
}

void CodeContainer::createFunction2(const string& name, Typed::VarType res, 
                                const string& arg1, Typed::VarType arg1_ty,
                                const string& arg2, Typed::VarType arg2_ty)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(arg1, InstBuilder::genBasicTyped(arg1_ty)));
    args.push_back(InstBuilder::genNamedTyped(arg2, InstBuilder::genBasicTyped(arg2_ty)));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    DeclareFunInst* fun = InstBuilder::genDeclareFunInst(name, fun_type);
    pushGlobalDeclare(fun);
}

void CodeContainer::createFunction3(const string& name, Typed::VarType res, 
                                const string& arg1, Typed::VarType arg1_ty,
                                const string& arg2, Typed::VarType arg2_ty,
                                const string& arg3, Typed::VarType arg3_ty)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(arg1, InstBuilder::genBasicTyped(arg1_ty)));
    args.push_back(InstBuilder::genNamedTyped(arg2, InstBuilder::genBasicTyped(arg2_ty)));
    args.push_back(InstBuilder::genNamedTyped(arg3, InstBuilder::genBasicTyped(arg3_ty)));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    DeclareFunInst* fun = InstBuilder::genDeclareFunInst(name, fun_type);
    pushGlobalDeclare(fun);
}

void CodeContainer::createFunction4(const string& name, Typed::VarType res, 
                                const string& arg1, Typed::VarType arg1_ty,
                                const string& arg2, Typed::VarType arg2_ty,
                                const string& arg3, Typed::VarType arg3_ty,
                                const string& arg4, Typed::VarType arg4_ty)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(arg1, InstBuilder::genBasicTyped(arg1_ty)));
    args.push_back(InstBuilder::genNamedTyped(arg2, InstBuilder::genBasicTyped(arg2_ty)));
    args.push_back(InstBuilder::genNamedTyped(arg3, InstBuilder::genBasicTyped(arg3_ty)));
    args.push_back(InstBuilder::genNamedTyped(arg4, InstBuilder::genBasicTyped(arg4_ty)));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    DeclareFunInst* fun = InstBuilder::genDeclareFunInst(name, fun_type);
    pushGlobalDeclare(fun);
}

