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
#include <stack>
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

struct Codeblock : public virtual Garbageable {
    BlockInst* fPreInst;      ///< code to execute at the begin
    BlockInst* fComputeInst;  ///< code to execute in the loop
    BlockInst* fPostInst;     ///< code to execute at the end
                              ///<
    Codeblock()
        : fPreInst(new BlockInst()), fComputeInst(new BlockInst()), fPostInst(new BlockInst())
    {
    }
};

struct CodeIFblock : public Codeblock {
    ValueInst* fCond;  ///< condition of the IF block

    CodeIFblock(ValueInst* cond) : Codeblock(), fCond(cond) {}
};

struct CodeUSblock : public Codeblock {
    ValueInst*  fUSfactor;  ///< upsampling factor of the US block
    std::string fLoopIndex;

    CodeUSblock(ValueInst* us_factor) : Codeblock(), fUSfactor(us_factor)
    {
        fLoopIndex = gGlobal->getFreshID("us");
    }
};

struct CodeDSblock : public Codeblock {
    ValueInst*  fDSfactor;  ///< downsampling factor of the US block
    std::string fDSCounter;

    CodeDSblock(ValueInst* ds_factor, const std::string& ds_counter)
        : Codeblock(), fDSfactor(ds_factor), fDSCounter(ds_counter)
    {
    }
};

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

    std::stack<Codeblock*> fCodeStack;  //< stack of IF/US/DS code blocks

    ValueInst* fSRFactor;

    int                  fUseCount;    ///< how many loops depend on this one
    std::list<CodeLoop*> fExtraLoops;  ///< extra loops that where in sequences

    std::set<Tree>      fRecDependencies;  ///< Loops having recursive dependencies must be merged
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
          fSRFactor(IB::genInt32NumInst(1)),
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
          fSRFactor(IB::genInt32NumInst(1)),
          fUseCount(0)
    {
    }

    StatementInst* pushPreComputeDSPMethod(StatementInst* inst)
    {
        if (fCodeStack.size() > 0) {
            fCodeStack.top()->fPreInst->pushBackInst(inst);
        } else {
            fPreInst->pushBackInst(inst);
        }
        return inst;
    }
    StatementInst* pushComputeDSPMethod(StatementInst* inst)
    {
        if (fCodeStack.size() > 0) {
            fCodeStack.top()->fComputeInst->pushBackInst(inst);
        } else {
            fComputeInst->pushBackInst(inst);
        }
        return inst;
    }
    StatementInst* pushPostComputeDSPMethod(StatementInst* inst)
    {
        if (fCodeStack.size() > 0) {
            fCodeStack.top()->fPostInst->pushBackInst(inst);
        } else {
            fPostInst->pushBackInst(inst);
        }
        return inst;
    }

    bool isRecursive() { return fIsRecursive; }

    int getIndex() { return fIndex; }

    std::set<CodeLoop*>& getForwardLoopDependencies() { return fForwardLoopDependencies; }
    std::set<CodeLoop*>& getBackwardLoopDependencies() { return fBackwardLoopDependencies; }

    ValueInst* getLoopIndex()
    {
        if (fCodeStack.size() > 0) {
            if (CodeUSblock* us_block = dynamic_cast<CodeUSblock*>(fCodeStack.top())) {
                return IB::genLoadLoopVar(us_block->fLoopIndex);
            }
        }
        return IB::genLoadLoopVar(fLoopIndex);
    }

    ValueInst* getSRFactor() { return fSRFactor; }

    ForLoopInst* generateScalarLoop(const std::string& counter, bool loop_var_in_bytes = false);

    // For SYFALA : loop with a fixed size (known at compile time)
    ForLoopInst* generateFixedScalarLoop();

    // For Rust backend
    SimpleForLoopInst*   generateSimpleScalarLoop(const std::string& counter);
    IteratorForLoopInst* generateSimpleScalarLoop(const std::vector<std::string>& iterators);

    BlockInst* generateOneSample();

    void generateDAGScalarLoop(BlockInst* block, ValueInst* count, bool omp);

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

    /**
     * Open a new IF block.
     * @param cond the condition of the IF block
     */
    void openIFblock(ValueInst* cond)
    {
        CodeIFblock* b = new CodeIFblock(cond);
        fCodeStack.push(b);
    }

    /**
     * Close the current/top IF block.
     */
    void closeIFblock()
    {
        CodeIFblock* b = dynamic_cast<CodeIFblock*>(fCodeStack.top());
        faustassert(b);
        fCodeStack.pop();
        BlockInst* then_block = new BlockInst();
        then_block->pushBackInst(b->fPreInst);
        then_block->pushBackInst(b->fComputeInst);
        then_block->pushBackInst(b->fPostInst);
        pushComputeDSPMethod(IB::genIfInst(b->fCond, then_block));
    }

    /**
     * Open a new US block.
     * @param us_factor the upsampling factor of the US block
     */
    void openUSblock(ValueInst* us_factor)
    {
        CodeUSblock* b = new CodeUSblock(us_factor);
        fCodeStack.push(b);
        // Adjust fSRFactor
        // fSRFactor = IB::genMul(fSRFactor, us_factor);
        // pushComputeDSPMethod(IB::genStoreStructVar("fIntSampleRate",
        // IB::genMul(IB::genLoadStructVar("fIntSampleRate"), us_factor)));
    }

    /**
     * Close the current/top US block.
     */
    void closeUSblock();

    /**
     * Open a new DS block.
     * @param us_factor the downsampling factor of the US block
     */
    void openDSblock(ValueInst* ds_factor, const std::string& ds_counter)
    {
        CodeDSblock* b = new CodeDSblock(ds_factor, ds_counter);
        fCodeStack.push(b);
        // Adjust fSRFactor
        // fSRFactor = IB::genDiv(fSRFactor, ds_factor);
        // pushComputeDSPMethod(IB::genStoreStructVar("fIntSampleRate",
        // IB::genDiv(IB::genLoadStructVar("fIntSampleRate"), ds_factor)));
    }

    /**
     * Close the current/top US block.
     */
    void closeDSblock();

    static void sortGraph(CodeLoop* root, lclgraph& V);
    static void computeUseCount(CodeLoop* l);
    static void groupSeqLoops(CodeLoop* l, std::set<CodeLoop*>& visited);
};

#endif
