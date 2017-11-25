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

#ifndef _CODE_LOOP_H
#define _CODE_LOOP_H

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

#include "tree.hh"
#include "fir_function_builder.hh"
#include "list.hh"
#include "garbageable.hh"

// Loop internal code

/*

On a des boucles indépendantes qui seront "connectées" avec des vecteurs

On voudrait pouvoir connecter des boucles et supprimer les vecteurs intermédiaires.

On part d'un DAG de loops, on veut pouvoir:

- mettre ce DAG sur la forme d'une sequence de boucle (tri topologique)
- "fusionner" toutes les boucles en une seule, donc en gros entraire le code des boucles et le fusionner

Scalarisation d'une boucle:

- identifier tous les vecteurs d'entrée et de sortie
- transformer les vecteur en scalaire
- transformer les accès (Load/Store) en accès scalaire

*/

class CodeLoop;

typedef set<CodeLoop*>  lclset;
typedef vector<lclset>  lclgraph;

class CodeLoop : public virtual Garbageable {

    friend class CodeContainer;

    private:

        bool fIsRecursive;                  ///< recursive loops can't be SIMDed
        Tree fRecSymbolSet;                 ///< recursive loops define a set of recursive symbol
        CodeLoop* const fEnclosingLoop;     ///< Loop from which this one originated
        int fSize;                          ///< number of iterations of the loop
        int fOrder;                         ///< used during topological sort
        int fIndex;

        BlockInst* fPreInst;
        BlockInst* fComputeInst;
        BlockInst* fPostInst;

        string fLoopIndex;

        int	fUseCount;                  ///< how many loops depend on this one
        list<CodeLoop*>	fExtraLoops;	///< extra loops that where in sequences

        set<Tree>      fRecDependencies;            ///< Loops having recursive dependencies must be merged
        set<CodeLoop*> fBackwardLoopDependencies;   ///< Loops that must be computed before this one
        set<CodeLoop*> fForwardLoopDependencies;    ///< Loops that will be computed after this one

        void pushBlock(BlockInst* block, BlockInst* loop)
        {
            list<StatementInst*>::const_iterator it;
            for (it = block->fCode.begin(); it != block->fCode.end(); it++) {
                loop->pushBackInst((*it));
            }
        }

        bool isEmpty();                 ///< true when the loop doesn't contain any line of code

        void absorb(CodeLoop* l);       ///< absorb a loop inside this one
        void concat(CodeLoop* l);

        // Graph sorting
        static void setOrder(CodeLoop* l, int order, lclgraph& V);
        static void setLevel(int order, const lclset& T1, lclset& T2, lclgraph& V);
        static void resetOrder(CodeLoop* l, set<CodeLoop*>& visited);

    public:

        ///< create a recursive loop
        CodeLoop(Tree recsymbol, CodeLoop* encl, string index_name, int size = 0)
            :fIsRecursive(true), fRecSymbolSet(singleton(recsymbol)), fEnclosingLoop(encl), fSize(size), fOrder(-1), fIndex(-1),
            fPreInst(new BlockInst()), fComputeInst(new BlockInst()), fPostInst(new BlockInst()), fLoopIndex(index_name), fUseCount(0)
        {}

        ///< create a non recursive loop
        CodeLoop(CodeLoop* encl, string index_name, int size = 0);
    
        StatementInst* pushComputePreDSPMethod(StatementInst* inst) { fPreInst->pushBackInst(inst); return inst; }
        StatementInst* pushComputeDSPMethod(StatementInst* inst) { fComputeInst->pushBackInst(inst); return inst; }
        StatementInst* pushComputePostDSPMethod(StatementInst* inst) { fPostInst->pushBackInst(inst); return inst;}

        bool isRecursive() { return fIsRecursive; }

        int getIndex() { return fIndex; }

        set<CodeLoop*>& getForwardLoopDependencies() { return fForwardLoopDependencies; }
        set<CodeLoop*>& getBackwardLoopDependencies() { return fBackwardLoopDependencies; }

        ValueInst* getLoopIndex()
        {
            return InstBuilder::genLoadLoopVar(fLoopIndex);
        }

        ForLoopInst* generateScalarLoop(const string& counter, bool loop_var_in_bytes = false);

        void generateDAGScalarLoop(BlockInst* block, DeclareVarInst* count, bool omp);
        void generateDAGVectorLoop(BlockInst* block, DeclareVarInst* count, bool omp, int size);

        void transform(DispatchVisitor* visitor)
        {
            // Transform extra loops
            for (list<CodeLoop*>::const_iterator s = fExtraLoops.begin(); s != fExtraLoops.end(); s++) {
                (*s)->transform(visitor);
            }
            fPreInst->accept(visitor);
            fComputeInst->accept(visitor);
            fPostInst->accept(visitor);
        }

        bool hasRecDependencyIn(Tree S);    ///< returns true is this loop has recursive dependencies
        void addBackwardDependency(CodeLoop* ls) { fBackwardLoopDependencies.insert(ls); }

        static void sortGraph(CodeLoop* root, lclgraph& V);
        static void computeUseCount(CodeLoop* l);
        static void groupSeqLoops(CodeLoop* l, set<CodeLoop*>& visited);

};

#endif
