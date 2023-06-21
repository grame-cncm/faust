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

#ifndef _CODE_LOOP_H
#define _CODE_LOOP_H

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "fir_function_builder.hh"
#include "garbageable.hh"
#include "list.hh"
#include "tree.hh"

// Loop internal code

/*
 
 We have independent loops that will be "connected" with vectors
 
 We would like to be able to connect loops and remove the intermediate vectors.
 
 We start from a DAG of loops, we want to be able to:
 
 - put this DAG on the form of a sequence of loops (topological sorting)
 - merge all the loops into one, so basically extract the loops code and merge it
 
 Scalarization of a loop:
 
 - identify all input and output vectors
 - transform the vectors into scalars
 - transform the accesses (Load/Store) into scalar accesses
 
*/

class CodeLoop;

typedef std::set<CodeLoop*> lclset;
typedef std::vector<lclset> lclgraph;

class CodeLoop : public virtual Garbageable {
    friend class CodeContainer;

   private:
    bool            fIsRecursive;    ///< recursive loops can't be SIMDed
    Tree            fRecSymbolSet;   ///< recursive loops define a set of recursive symbol
    CodeLoop* const fEnclosingLoop;  ///< Loop from which this one originated
    int             fSize;           ///< number of iterations of the loop
    int             fOrder;          ///< used during topological sort
    int             fIndex;

    BlockInst* fPreInst;
    BlockInst* fComputeInst;
    BlockInst* fPostInst;

    std::string fLoopIndex;

    int             fUseCount;    ///< how many loops depend on this one
    std::list<CodeLoop*> fExtraLoops;  ///< extra loops that where in sequences

    std::set<Tree>      fRecDependencies;           ///< Loops having recursive dependencies must be merged
    std::set<CodeLoop*> fBackwardLoopDependencies;  ///< Loops that must be computed before this one
    std::set<CodeLoop*> fForwardLoopDependencies;   ///< Loops that will be computed after this one

    void pushBlock(BlockInst* block, BlockInst* loop)
    {
        for (const auto& it : block->fCode) {
            loop->pushBackInst(it);
        }
    }

    bool isEmpty();  ///< true when the loop doesn't contain any line of code

    void absorb(CodeLoop* l);  ///< absorb a loop inside this one
    void concat(CodeLoop* l);

    // Graph sorting
    static void setOrder(CodeLoop* l, int order, lclgraph& V);
    static void setLevel(int order, const lclset& T1, lclset& T2, lclgraph& V);
    static void resetOrder(CodeLoop* l, std::set<CodeLoop*>& visited);

   public:
    ///< create a recursive loop
    CodeLoop(Tree recsymbol, CodeLoop* encl, const std::string& index_name, int size = 0)
        : fIsRecursive(true),
          fRecSymbolSet(singleton(recsymbol)),
          fEnclosingLoop(encl),
          fSize(size),
          fOrder(-1),
          fIndex(-1),
          fPreInst(new BlockInst()),
          fComputeInst(new BlockInst()),
          fPostInst(new BlockInst()),
          fLoopIndex(index_name),
          fUseCount(0)
    {
    }

    ///< create a non recursive loop
    CodeLoop(CodeLoop* encl, const std::string& index_name, int size = 0)
        : fIsRecursive(false),
          fRecSymbolSet(gGlobal->nil),
          fEnclosingLoop(encl),
          fSize(size),
          fOrder(-1),
          fIndex(-1),
          fPreInst(new BlockInst()),
          fComputeInst(new BlockInst()),
          fPostInst(new BlockInst()),
          fLoopIndex(index_name),
          fUseCount(0)
    {
    }

    StatementInst* pushPreComputeDSPMethod(StatementInst* inst)
    {
        fPreInst->pushBackInst(inst);
        return inst;
    }
    StatementInst* pushComputeDSPMethod(StatementInst* inst)
    {
        fComputeInst->pushBackInst(inst);
        return inst;
    }
    StatementInst* pushPostComputeDSPMethod(StatementInst* inst)
    {
        fPostInst->pushBackInst(inst);
        return inst;
    }

    bool isRecursive() { return fIsRecursive; }

    int getIndex() { return fIndex; }

    std::set<CodeLoop*>& getForwardLoopDependencies() { return fForwardLoopDependencies; }
    std::set<CodeLoop*>& getBackwardLoopDependencies() { return fBackwardLoopDependencies; }

    ValueInst* getLoopIndex() { return InstBuilder::genLoadLoopVar(fLoopIndex); }

    ForLoopInst* generateScalarLoop(const std::string& counter, bool loop_var_in_bytes = false);

    // For Rust backend
    SimpleForLoopInst* generateSimpleScalarLoop(const std::string& counter);
    IteratorForLoopInst* generateSimpleScalarLoop(const std::vector<std::string>& iterators);

    BlockInst* generateOneSample();

    void generateDAGScalarLoop(BlockInst* block, LoadVarInst* count, bool omp);

    void transform(DispatchVisitor* visitor)
    {
        // Transform extra loops
        for (const auto& s : fExtraLoops) {
            s->transform(visitor);
        }
        fPreInst->accept(visitor);
        fComputeInst->accept(visitor);
        fPostInst->accept(visitor);
    }

    bool hasRecDependencyIn(Tree S);  ///< returns true is this loop has recursive dependencies
    void addBackwardDependency(CodeLoop* ls) { fBackwardLoopDependencies.insert(ls); }

    static void sortGraph(CodeLoop* root, lclgraph& V);
    static void computeUseCount(CodeLoop* l);
    static void groupSeqLoops(CodeLoop* l, std::set<CodeLoop*>& visited);
};

#endif
