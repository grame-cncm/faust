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

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "code_loop.hh"
#include "fir_to_fir.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

ForLoopInst* CodeLoop::generateScalarLoop(const string& counter, bool loop_var_in_bytes)
{
    DeclareVarInst* loop_decl =
        IB::genDecLoopVar(fLoopIndex, IB::genInt32Typed(), IB::genInt32NumInst(0));
    ValueInst*    loop_end;
    StoreVarInst* loop_increment;

    if (loop_var_in_bytes) {
        loop_end = IB::genLessThan(
            loop_decl->load(), IB::genMul(IB::genInt32NumInst((int)pow(2, gGlobal->gFloatSize + 1)),
                                          IB::genLoadFunArgsVar(counter)));
        loop_increment =
            loop_decl->store(IB::genAdd(loop_decl->load(), (int)pow(2, gGlobal->gFloatSize + 1)));
    } else {
        loop_end       = IB::genLessThan(loop_decl->load(), IB::genLoadFunArgsVar(counter));
        loop_increment = loop_decl->store(IB::genAdd(loop_decl->load(), 1));
    }

    BlockInst*   block = generateOneSample();
    ForLoopInst* loop =
        IB::genForLoopInst(loop_decl, loop_end, loop_increment, block, fIsRecursive);

    BasicCloneVisitor cloner;
    return static_cast<ForLoopInst*>(loop->clone(&cloner));
}

ForLoopInst* CodeLoop::generateFixedScalarLoop()
{
    DeclareVarInst* loop_decl =
        IB::genDecLoopVar(fLoopIndex, IB::genInt32Typed(), IB::genInt32NumInst(0));

    ValueInst*    loop_end       = IB::genLessThan(loop_decl->load(), FIRIndex(gGlobal->gVecSize));
    StoreVarInst* loop_increment = loop_decl->store(IB::genAdd(loop_decl->load(), 1));

    BlockInst*   block = generateOneSample();
    ForLoopInst* loop =
        IB::genForLoopInst(loop_decl, loop_end, loop_increment, block, fIsRecursive);

    BasicCloneVisitor cloner;
    return static_cast<ForLoopInst*>(loop->clone(&cloner));
}

// To be used for the 'rust' backend
SimpleForLoopInst* CodeLoop::generateSimpleScalarLoop(const string& counter)
{
    ValueInst* upper_bound = IB::genLoadFunArgsVar(counter);
    ValueInst* lower_bound = IB::genInt32NumInst(0);

    BlockInst*         block = generateOneSample();
    SimpleForLoopInst* loop =
        IB::genSimpleForLoopInst(fLoopIndex, upper_bound, lower_bound, false, block);

    BasicCloneVisitor cloner;
    return static_cast<SimpleForLoopInst*>(loop->clone(&cloner));
}

IteratorForLoopInst* CodeLoop::generateSimpleScalarLoop(const std::vector<string>& iterators)
{
    std::vector<NamedAddress*> iterators1;
    for (const auto& it : iterators) {
        iterators1.push_back(IB::genNamedAddress(it, Address::kStack));
    }

    BlockInst*           block = generateOneSample();
    IteratorForLoopInst* loop  = IB::genIteratorForLoopInst(iterators1, false, block);

    BasicCloneVisitor cloner;
    return static_cast<IteratorForLoopInst*>(loop->clone(&cloner));
}

// Generate the scalar sample code
BlockInst* CodeLoop::generateOneSample()
{
    BlockInst* block = IB::genBlockInst();

    pushBlock(fPreInst, block);
    pushBlock(fComputeInst, block);
    pushBlock(fPostInst, block);

    // Expand and rewrite ControlInst as 'if (cond) {....}' instructions
    ControlExpander exp;
    block = exp.getCode(block);

    // Rewrite "Rec/Vec" indexes in iZone/fZone access
    if (gGlobal->gMemoryManager >= 1) {
        block = gGlobal->gIntZone->getCode(block);
        block = gGlobal->gRealZone->getCode(block);
        return block;
    } else {
        BasicCloneVisitor cloner;
        return static_cast<BlockInst*>(block->clone(&cloner));
    }
}

void CodeLoop::generateDAGScalarLoop(BlockInst* block, ValueInst* count, bool omp)
{
    // Generate code for extra loops
    for (list<CodeLoop*>::const_iterator s = fExtraLoops.begin(); s != fExtraLoops.end(); s++) {
        (*s)->generateDAGScalarLoop(block, count, omp);
    }

    // Generate code before the loop
    if (fPreInst->fCode.size() > 0) {
        block->pushBackInst(IB::genLabelInst("/* Pre code */"));
        if (omp) {
            block->pushBackInst(IB::genLabelInst("#pragma omp single"));
        }
        pushBlock(fPreInst, block);
    }

    // Generate loop code
    if (fComputeInst->fCode.size() > 0) {
        DeclareVarInst* loop_decl =
            IB::genDecLoopVar(fLoopIndex, IB::genInt32Typed(), IB::genInt32NumInst(0));
        ValueInst*    loop_end       = IB::genLessThan(loop_decl->load(), count);
        StoreVarInst* loop_increment = loop_decl->store(IB::genAdd(loop_decl->load(), 1));

        block->pushBackInst(IB::genLabelInst("/* Compute code */"));
        if (omp) {
            block->pushBackInst(IB::genLabelInst("#pragma omp for"));
        }

        BlockInst* block1 = IB::genBlockInst();
        pushBlock(fComputeInst, block1);

        ForLoopInst* loop =
            IB::genForLoopInst(loop_decl, loop_end, loop_increment, block1, fIsRecursive);
        block->pushBackInst(loop);
    }

    // Generate code after the loop
    if (fPostInst->fCode.size() > 0) {
        block->pushBackInst(IB::genLabelInst("/* Post code */"));
        if (omp) {
            block->pushBackInst(IB::genLabelInst("#pragma omp single"));
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
    return fPreInst->fCode.empty() && fComputeInst->fCode.empty() && fPostInst->fCode.empty() &&
           (fExtraLoops.begin() == fExtraLoops.end());
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
    while (l && isNil(setIntersection(l->fRecSymbolSet, S))) {
        l = l->fEnclosingLoop;
    }
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
    fBackwardLoopDependencies.insert(l->fBackwardLoopDependencies.begin(),
                                     l->fBackwardLoopDependencies.end());

    // add the line of code of the absorbed loop
    fPreInst->fCode.insert(fPreInst->fCode.end(), l->fPreInst->fCode.begin(),
                           l->fPreInst->fCode.end());
    fComputeInst->fCode.insert(fComputeInst->fCode.end(), l->fComputeInst->fCode.begin(),
                               l->fComputeInst->fCode.end());
    fPostInst->fCode.insert(fPostInst->fCode.begin(), l->fPostInst->fCode.begin(),
                            l->fPostInst->fCode.end());

    // copy loop index
    fLoopIndex = l->fLoopIndex;
}

void CodeLoop::concat(CodeLoop* l)
{
    // faustassert(l->fUseCount == 1);
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
    if (l->fOrder >= 0) {
        V[l->fOrder].erase(l);
    }
    l->fOrder = order;
    V[order].insert(l);
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
        for (lclset::const_iterator p = l->fBackwardLoopDependencies.begin();
             p != l->fBackwardLoopDependencies.end(); p++) {
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
        T1 = T2;
        T2.clear();
        level++;
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
        for (lclset::iterator p = l->fBackwardLoopDependencies.begin();
             p != l->fBackwardLoopDependencies.end(); p++) {
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
            for (lclset::iterator p = l->fBackwardLoopDependencies.begin();
                 p != l->fBackwardLoopDependencies.end(); p++) {
                groupSeqLoops(*p, visited);
            }
        }
    }
}

void CodeLoop::closeODblock()
{
    CodeODblock* b = dynamic_cast<CodeODblock*>(fCodeStack.top());
    faustassert(b);
    fCodeStack.pop();

    BlockInst* od_block = new BlockInst();
    od_block->pushBackInst(b->fPreInst);
    od_block->pushBackInst(b->fComputeInst);
    od_block->pushBackInst(b->fPostInst);

    // pushComputeDSPMethod(IB::genIfInst(b->fCond, then_block));

    DeclareVarInst* loop_decl =
        IB::genDecLoopVar(b->fLoopIndex, IB::genInt32Typed(), IB::genInt32NumInst(0));
    ValueInst*    loop_end = IB::genLessThan(loop_decl->load(), b->fODfactor);
    StoreVarInst* loop_inc = loop_decl->store(IB::genAdd(loop_decl->load(), 1));

    ForLoopInst* loop = IB::genForLoopInst(loop_decl, loop_end, loop_inc);
    loop->pushFrontInst(od_block);
    pushComputeDSPMethod(loop);
}

void CodeLoop::closeUSblock()
{
    CodeUSblock* b = dynamic_cast<CodeUSblock*>(fCodeStack.top());
    faustassert(b);
    fCodeStack.pop();

    BlockInst* us_block = new BlockInst();
    us_block->pushBackInst(b->fPreInst);
    us_block->pushBackInst(b->fComputeInst);
    us_block->pushBackInst(b->fPostInst);

    DeclareVarInst* loop_decl =
        IB::genDecLoopVar(b->fLoopIndex, IB::genInt32Typed(), IB::genInt32NumInst(0));
    ValueInst*    loop_end = IB::genLessThan(loop_decl->load(), b->fUSfactor);
    StoreVarInst* loop_inc = loop_decl->store(IB::genAdd(loop_decl->load(), 1));

    ForLoopInst* loop = IB::genForLoopInst(loop_decl, loop_end, loop_inc);
    loop->pushFrontInst(us_block);
    pushComputeDSPMethod(loop);
}

void CodeLoop::closeDSblock()
{
    CodeDSblock* b = dynamic_cast<CodeDSblock*>(fCodeStack.top());
    faustassert(b);
    fCodeStack.pop();

    BlockInst* ds_block1 = new BlockInst();
    ds_block1->pushBackInst(b->fPreInst);
    ds_block1->pushBackInst(b->fComputeInst);
    ds_block1->pushBackInst(b->fPostInst);

    BlockInst* ds_block2 = new BlockInst();
    ValueInst* cond      = IB::genNotEqual(b->fDSfactor, IB::genInt32NumInst(0));
    if (IB::isOne(cond)) {
        ds_block2->pushBackInst(IB::genIfInst(
            IB::genEqual(IB::genRem(IB::genLoadStructVar(b->fDSCounter), b->fDSfactor),
                         IB::genInt32NumInst(0)),
            ds_block1));
    } else {
        ds_block2->pushBackInst(IB::genIfInst(
            IB::genAnd(cond,
                       IB::genEqual(IB::genRem(IB::genLoadStructVar(b->fDSCounter), b->fDSfactor),
                                    IB::genInt32NumInst(0))),
            ds_block1));
    }

    pushComputeDSPMethod(ds_block2);
}
