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

#include "code_loop.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

CodeLoop::CodeLoop(CodeLoop* encl, string index_name, int size)
        :fIsRecursive(false), fRecSymbolSet(gGlobal->nil), fEnclosingLoop(encl), fSize(size), fOrder(-1), fIndex(-1),
        fPreInst(new BlockInst()), fComputeInst(new BlockInst()), fPostInst(new BlockInst()), fLoopIndex(index_name), fUseCount(0)
    {}

ForLoopInst* CodeLoop::generateScalarLoop(const string& counter, bool loop_var_in_bytes)
{
    DeclareVarInst* loop_decl = InstBuilder::genDecLoopVar(fLoopIndex, InstBuilder::genBasicTyped(Typed::kInt32), InstBuilder::genInt32NumInst(0));
    ValueInst* loop_end;
    StoreVarInst* loop_increment;
    
    if (loop_var_in_bytes) {
        loop_end = InstBuilder::genLessThan(loop_decl->load(),
                                            InstBuilder::genMul(InstBuilder::genInt32NumInst(pow(2, gGlobal->gFloatSize + 1)),
                                                                InstBuilder::genLoadFunArgsVar(counter)));
        loop_increment = loop_decl->store(InstBuilder::genAdd(loop_decl->load(), pow(2, gGlobal->gFloatSize + 1)));
    } else {
        loop_end = InstBuilder::genLessThan(loop_decl->load(), InstBuilder::genLoadFunArgsVar(counter));
        loop_increment = loop_decl->store(InstBuilder::genAdd(loop_decl->load(), 1));
    }

    BlockInst* block = InstBuilder::genBlockInst();
    pushBlock(fPreInst, block);
    pushBlock(fComputeInst, block);
    pushBlock(fPostInst, block);
    
    ForLoopInst* loop = InstBuilder::genForLoopInst(loop_decl, loop_end, loop_increment, block);

    BasicCloneVisitor cloner;
    return static_cast<ForLoopInst*>(loop->clone(&cloner));
}

struct VectorCloneVisitor : public BasicCloneVisitor {

    int fSize;

    VectorCloneVisitor(int fize):fSize(fize)
    {}

    /*
    virtual Typed* visit(BasicTyped* typed)
    {
        BasicCloneVisitor cloner;
        return new VectorTyped(dynamic_cast<BasicTyped*>(typed->clone(&cloner)), fSize);
    }
    */

    virtual ValueInst* visit(LoadVarInst* inst)
    {
        if (inst->fAddress->getAccess() != Address::kLoop) {
            // Switch to scalar mode for address indexing
            return new LoadVarInst(inst->fAddress->clone(new BasicCloneVisitor()), fSize);
        } else {
            return BasicCloneVisitor::visit(inst);
        }
     }

    virtual ValueInst* visit(LoadVarAddressInst* inst)
    {
        if (inst->fAddress->getAccess() != Address::kLoop) {
            // Switch to scalar mode for address indexing
            return new LoadVarAddressInst(inst->fAddress->clone(new BasicCloneVisitor()), fSize);
        }  else {
            return BasicCloneVisitor::visit(inst);
        }
    }

    virtual ValueInst* visit(CastInst* inst)
    {
        ValueInst* cloned_inst = inst->fInst->clone(this);

        // Vector result when argument is vectorized
        if (cloned_inst->fSize > 1) {
            return new CastInst(cloned_inst, inst->fType->clone(this), fSize);
        }  else {
            return BasicCloneVisitor::visit(inst);
        }
    }

    virtual ValueInst* visit(FloatNumInst* inst) { return new FloatNumInst(inst->fNum, fSize); }
    virtual ValueInst* visit(Int32NumInst* inst) { return new Int32NumInst(inst->fNum, fSize); }
    virtual ValueInst* visit(BoolNumInst* inst) { return new BoolNumInst(inst->fNum, fSize); }
    virtual ValueInst* visit(DoubleNumInst* inst) { return new DoubleNumInst(inst->fNum, fSize); }

    virtual ValueInst* visit(BinopInst* inst)
    {
        ValueInst* cloned_inst1 = inst->fInst1->clone(this);
        ValueInst* cloned_inst2 = inst->fInst2->clone(this);

        // Vector result when both arguments are vectorized
        if (cloned_inst1->fSize > 1 && cloned_inst2->fSize > 1) {
            return new BinopInst(inst->fOpcode, cloned_inst1, cloned_inst2, fSize);
        } else {
            return BasicCloneVisitor::visit(inst);
        }
    }

    virtual ValueInst* visit(FunCallInst* inst)
    {
        list<ValueInst*> cloned_args;
        bool all_vectorized = true;

        for (list<ValueInst*>::const_iterator it = inst->fArgs.begin(); it != inst->fArgs.end(); it++) {
            ValueInst* cloned_arg = (*it)->clone(this);
            all_vectorized &= (cloned_arg->fSize > 1);
            cloned_args.push_back(cloned_arg);
        }

        // Vector result when all arguments are vectorized
        if (all_vectorized) {
            return new FunCallInst(inst->fName, cloned_args, inst->fMethod, fSize);
        } else {
            return BasicCloneVisitor::visit(inst);
        }
    }

    virtual ValueInst* visit(Select2Inst* inst)
    {
        ValueInst* cloned_inst = inst->fCond->clone(this);

        // Vector result when fCond is vectorized
        if (cloned_inst->fSize > 1) {
            return new Select2Inst(cloned_inst, inst->fThen->clone(this), inst->fElse->clone(this), fSize);
        } else {
            return BasicCloneVisitor::visit(inst);
        }
    }

};

void CodeLoop::generateDAGVectorLoop(BlockInst* block, DeclareVarInst* count, bool omp, int size)
{
    // TODO
    // 1) Vectorize access to all scalar that are not "kLoop" type: declare a Vector version of them, then transform Load/Store access.
    // 2) Vectorize access to all constant numbers (Load)
    // 3) Vectorize all array access (Load/Store)

    // Generate code for extra loops
    for (list<CodeLoop*>::const_iterator s = fExtraLoops.begin(); s != fExtraLoops.end(); s++) {
        (*s)->generateDAGVectorLoop(block, count, omp, size);
    }

    // Generate code before the loop
    if (fPreInst->fCode.size() > 0) {
        block->pushBackInst(InstBuilder::genLabelInst("/* Pre code $/"));
        if (omp) {
            block->pushBackInst(InstBuilder::genLabelInst("#pragma omp single"));
        }
        pushBlock(fPreInst, block);
    }

    // Generate loop code
    if (fComputeInst->fCode.size() > 0) {

        DeclareVarInst* loop_decl = InstBuilder::genDecLoopVar(fLoopIndex, InstBuilder::genBasicTyped(Typed::kInt32), InstBuilder::genInt32NumInst(0));
        ValueInst* loop_end = InstBuilder::genLessThan(loop_decl->load(), count->load());
        StoreVarInst* loop_increment = loop_decl->store(InstBuilder::genAdd(loop_decl->load(), size));

        VectorCloneVisitor vector_cloner(size);
        BlockInst* cloned = static_cast<BlockInst*>(fComputeInst->clone(&vector_cloner));

        block->pushBackInst(InstBuilder::genLabelInst("/* Compute code */"));
        if (omp) {
            block->pushBackInst(InstBuilder::genLabelInst("#pragma omp for"));
        }

        BlockInst* block1 = InstBuilder::genBlockInst();
        pushBlock(cloned, block1);

        ForLoopInst* loop = InstBuilder::genForLoopInst(loop_decl, loop_end, loop_increment, block1);
        block->pushBackInst(loop);
    }

    // Generate code after the loop
    if (fPostInst->fCode.size() > 0) {
        block->pushBackInst(InstBuilder::genLabelInst("/* Post code */"));
        if (omp) {
            block->pushBackInst(InstBuilder::genLabelInst("#pragma omp single"));
        }
        pushBlock(fPostInst, block);
    }
}

void CodeLoop::generateDAGScalarLoop(BlockInst* block, DeclareVarInst* count, bool omp)
{
    // Generate code for extra loops
    for (list<CodeLoop*>::const_iterator s = fExtraLoops.begin(); s != fExtraLoops.end(); s++) {
        (*s)->generateDAGScalarLoop(block, count, omp);
    }

    // Generate code before the loop
    if (fPreInst->fCode.size() > 0) {
        block->pushBackInst(InstBuilder::genLabelInst("/* Pre code */"));
        if (omp) {
            block->pushBackInst(InstBuilder::genLabelInst("#pragma omp single"));
        }
        pushBlock(fPreInst, block);
    }

    // Generate loop code
    if (fComputeInst->fCode.size() > 0) {

        DeclareVarInst* loop_decl = InstBuilder::genDecLoopVar(fLoopIndex, InstBuilder::genBasicTyped(Typed::kInt32), InstBuilder::genInt32NumInst(0));
        ValueInst* loop_end = InstBuilder::genLessThan(loop_decl->load(), count->load());
        StoreVarInst* loop_increment = loop_decl->store(InstBuilder::genAdd(loop_decl->load(), 1));

        block->pushBackInst(InstBuilder::genLabelInst("/* Compute code */"));
        if (omp) {
            block->pushBackInst(InstBuilder::genLabelInst("#pragma omp for"));
        }

        BlockInst* block1 = InstBuilder::genBlockInst();
        pushBlock(fComputeInst, block1);

        ForLoopInst* loop = InstBuilder::genForLoopInst(loop_decl, loop_end, loop_increment, block1);
        block->pushBackInst(loop);
    }

    // Generate code after the loop
    if (fPostInst->fCode.size() > 0) {
        block->pushBackInst(InstBuilder::genLabelInst("/* Post code */"));
        if (omp) {
            block->pushBackInst(InstBuilder::genLabelInst("#pragma omp single"));
        }
        pushBlock(fPostInst, block);
    }
}

/**
 * Test if a loop is empty that is if it contains no lines of code.
 * @return true if the loop is empty
 */
bool CodeLoop::isEmpty()
{
    return fPreInst->fCode.empty() && fComputeInst->fCode.empty() && fPostInst->fCode.empty() && (fExtraLoops.begin() == fExtraLoops.end());
}

/**
 * A loop with recursive dependencies can't be run alone.
 * It must be included into another loop.
 * returns true is this loop has recursive dependencies
 * and must be included in an enclosing loop
 */

bool CodeLoop::hasRecDependencyIn(Tree S)
{
    CodeLoop* l = this;
    while (l && isNil(setIntersection(l->fRecSymbolSet,S))) l=l->fEnclosingLoop;
    return l != 0;
}

/**
 * Absorb a loop by copying its recursive dependencies, its loop dependencies
 * and its lines of exec and post exec code.
 * @param l the Loop to be absorbed
 */
void CodeLoop::absorb(CodeLoop* l)
{
    // the loops must have the same number of iterations
    faustassert(fSize == l->fSize);
    fRecSymbolSet = setUnion(fRecSymbolSet, l->fRecSymbolSet);

    // update loop dependencies by adding those from the absorbed loop
    fBackwardLoopDependencies.insert(l->fBackwardLoopDependencies.begin(), l->fBackwardLoopDependencies.end());

    // add the line of code of the absorbed loop
    fPreInst->fCode.insert(fPreInst->fCode.end(), l->fPreInst->fCode.begin(), l->fPreInst->fCode.end());
    fComputeInst->fCode.insert(fComputeInst->fCode.end(), l->fComputeInst->fCode.begin(), l->fComputeInst->fCode.end());
    fPostInst->fCode.insert(fPostInst->fCode.begin(), l->fPostInst->fCode.begin(), l->fPostInst->fCode.end());

    // copy loop index
    fLoopIndex = l->fLoopIndex;
}

void CodeLoop::concat(CodeLoop* l)
{
	//faustassert(l->fUseCount == 1);
	faustassert(fBackwardLoopDependencies.size() == 1);
	faustassert((*fBackwardLoopDependencies.begin()) == l);

	fExtraLoops.push_front(l);
	fBackwardLoopDependencies = l->fBackwardLoopDependencies;
}

// Graph sorting

void CodeLoop::setOrder(CodeLoop* l, int order, lclgraph& V)
{
    faustassert(l);
    V.resize(order + 1);
    if (l->fOrder >= 0) { V[l->fOrder].erase(l); }
    l->fOrder = order; V[order].insert(l);
}

void CodeLoop::setLevel(int order, const lclset& T1, lclset& T2, lclgraph& V)
{
    for (lclset::const_iterator p = T1.begin(); p != T1.end(); p++) {
        setOrder(*p, order, V);
        T2.insert((*p)->fBackwardLoopDependencies.begin(), (*p)->fBackwardLoopDependencies.end());
    }
}

void CodeLoop::resetOrder(CodeLoop* l, set<CodeLoop*>& visited)
{
    // Not yet visited...
    if (visited.find(l) == visited.end()) {
        visited.insert(l);
        l->fOrder = -1;
        for (lclset::const_iterator p = l->fBackwardLoopDependencies.begin(); p != l->fBackwardLoopDependencies.end(); p++) {
            resetOrder(*p, visited);
        }
    }
}

void CodeLoop::sortGraph(CodeLoop* root, lclgraph& V)
{
    faustassert(root);
    set<CodeLoop*> visited;
    resetOrder(root, visited);
    
    lclset T1, T2;
    T1.insert(root);
    int level = 0;
    V.clear();
    
    do {
        setLevel(level, T1, T2, V);
        T1 = T2; T2.clear(); level++;
    } while (T1.size() > 0);

    // Erase empty levels
    lclgraph::iterator p = V.begin();
    while (p != V.end()) {
        if ((*p).size() == 1 && (*(*p).begin())->isEmpty()) {
            p = V.erase(p);
        } else {
            p++;
        }
    }
}

/**
 * Compute how many time each loop is used in a DAG
 */
void CodeLoop::computeUseCount(CodeLoop* l)
{
	l->fUseCount++;
	if (l->fUseCount == 1) {
		for (lclset::iterator p =l->fBackwardLoopDependencies.begin(); p!=l->fBackwardLoopDependencies.end(); p++) {
		    computeUseCount(*p);
		}
	}
}

/**
 * Group together sequences of loops
 */
void CodeLoop::groupSeqLoops(CodeLoop* l, set<CodeLoop*>& visited)
{
    if (visited.find(l) == visited.end()) {
        visited.insert(l);
        int n = int(l->fBackwardLoopDependencies.size());
        if (n == 0) {
            return;
        } else if (n == 1) {
            CodeLoop* f = *(l->fBackwardLoopDependencies.begin());
            if (f->fUseCount == 1) {
                l->concat(f);
                groupSeqLoops(l, visited);
            } else {
                groupSeqLoops(f, visited);
            }
            return;
        } else if (n > 1) {
            for (lclset::iterator p =l->fBackwardLoopDependencies.begin(); p!=l->fBackwardLoopDependencies.end(); p++) {
                groupSeqLoops(*p, visited);
            }
        }
    }
}
