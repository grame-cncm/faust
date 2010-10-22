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

using namespace std;

ForLoopInst* CodeLoop::getScalarLoop()
{
    // Here we assume that the generated loop will be embedded in a function where a "count" parameter is defined.
    string index = "i";

    DeclareVarInst* loop_init = InstBuilder::genDeclareVarInst(InstBuilder::genNamedAddress(index, Address::kLoop), InstBuilder::genBasicTyped(Typed::kInt), InstBuilder::genIntNumInst(0));
    ValueInst* loop_end = InstBuilder::genBinopInst(kLT,
                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("count", Address::kFunArgs)));
    StoreVarInst* loop_increment = InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(index, Address::kLoop),
                                            InstBuilder::genBinopInst(kAdd,
                                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                                    InstBuilder::genIntNumInst(1)));

    ForLoopInst* loop = InstBuilder::genForLoopInst(loop_init, loop_end, loop_increment);
    pushLoop(fPreInst, loop);
    pushLoop(fComputeInst, loop);
    pushLoop(fPostInst, loop);
    BasicCloneVisitor cloner;
    return dynamic_cast<ForLoopInst*>(loop->clone(&cloner));
}

void CodeLoop::generateVectorizedLoop(BlockInst* block, int size)
{
    // TODO
    // 1) Vectorize access to all scalar that are not "kLoop" type: declare a Vector version of them, then transform Load/Store access.
    // 2) Vectorize access to all constant numbers (Load)
    // 3) Vectorize all array access (Load/Store)
  
    // Here we assume that the generated loop will be embedded in a function where a "count" parameter is defined.
    string index = "i";

    // Generate code before the loop
    if (fPreInst->fCode.size() > 0) {
        block->pushBackInst(InstBuilder::genLabelInst("// Pre code"));
        pushBlock(fPreInst, block);
    }

    // Generate loop code
    if (fComputeInst->fCode.size() > 0) {

        DeclareVarInst* loop_init = InstBuilder::genDeclareVarInst(InstBuilder::genNamedAddress(index, Address::kLoop), InstBuilder::genBasicTyped(Typed::kInt), InstBuilder::genIntNumInst(0));
        ValueInst* loop_end = InstBuilder::genBinopInst(kLT,
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                     InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("count", Address::kStack)));
        StoreVarInst* loop_increment = InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(index, Address::kLoop),
                                            InstBuilder::genBinopInst(kAdd,
                                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                                    InstBuilder::genIntNumInst(size)));

        ForLoopInst* loop = InstBuilder::genForLoopInst(loop_init, loop_end, loop_increment);

        block->pushBackInst(InstBuilder::genLabelInst("// Compute code"));
        block->pushBackInst(loop);

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
                    return new LoadVarInst(inst->fAddress->clone(this), fSize); 
                } else {
                    BasicCloneVisitor cloner;
                    return inst->clone(&cloner);
                }
            }
            
            virtual ValueInst* visit(LoadVarAddressInst* inst) 
            { 
                if (inst->fAddress->getAccess() != Address::kLoop) {
                    return new LoadVarAddressInst(inst->fAddress->clone(this), fSize); 
                } else {
                    BasicCloneVisitor cloner;
                    return inst->clone(&cloner);
                }
            }
            
            virtual ValueInst* visit(CastNumInst* inst) 
            { 
                ValueInst* cloned_inst = inst->fInst->clone(this);
                
                // Vector result when argument is vectorized
                if (cloned_inst->fSize > 1) {
                    return new CastNumInst(cloned_inst, inst->fTyped->clone(this), fSize); 
                } else {
                    BasicCloneVisitor cloner;
                    return inst->clone(&cloner);
                }
            }
          
            virtual ValueInst* visit(FloatNumInst* inst) { return new FloatNumInst(inst->fNum, fSize); }
            virtual ValueInst* visit(IntNumInst* inst) { return new IntNumInst(inst->fNum, fSize); }
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
                    BasicCloneVisitor cloner;
                    return inst->clone(&cloner);
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
                    BasicCloneVisitor cloner;
                    return inst->clone(&cloner);
                }
            }
            
            virtual ValueInst* visit(Select2Inst* inst) 
            { 
                ValueInst* cloned_inst = inst->fCond->clone(this);
                
                // Vector result when fCond is vectorized
                if (cloned_inst->fSize > 1) { 
                    return new Select2Inst(cloned_inst, inst->fThen->clone(this), inst->fElse->clone(this), fSize); 
                } else {
                    BasicCloneVisitor cloner;
                    return inst->clone(&cloner);
                }
            }

        };

        VectorCloneVisitor vector_cloner(size);
        BlockInst* cloned = dynamic_cast<BlockInst*>(fComputeInst->clone(&vector_cloner));
        pushLoop(cloned, loop);
    }

    // Generate code after the loop
    if (fPostInst->fCode.size() > 0) {
        block->pushBackInst(InstBuilder::genLabelInst("// Post code"));
        pushBlock(fPostInst, block);
    }
}

void CodeLoop::generateVecLoop(BlockInst* block)
{
    // Here we assume that the generated loop will be embedded in a function where a "count" parameter is defined.
    string index = "i";

    // Generate code before the loop
    if (fPreInst->fCode.size() > 0) {
        block->pushBackInst(InstBuilder::genLabelInst("// Pre code"));
        pushBlock(fPreInst, block);
    }

    // Generate loop code
    if (fComputeInst->fCode.size() > 0) {
        DeclareVarInst* loop_init = InstBuilder::genDeclareVarInst(InstBuilder::genNamedAddress(index, Address::kLoop), InstBuilder::genBasicTyped(Typed::kInt), InstBuilder::genIntNumInst(0));
        ValueInst* loop_end = InstBuilder::genBinopInst(kLT,
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("count", Address::kStack)));
        StoreVarInst* loop_increment = InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(index, Address::kLoop),
                                            InstBuilder::genBinopInst(kAdd,
                                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                                    InstBuilder::genIntNumInst(1)));

        ForLoopInst* loop = InstBuilder::genForLoopInst(loop_init, loop_end, loop_increment);
        block->pushBackInst(InstBuilder::genLabelInst("// Compute code"));
        pushLoop(fComputeInst, loop);
        block->pushBackInst(loop);
    }

    // Generate code after the loop
    if (fPostInst->fCode.size() > 0) {
        block->pushBackInst(InstBuilder::genLabelInst("// Post code"));
        pushBlock(fPostInst, block);
    }
}

void CodeLoop::generateVecLoop1(BlockInst* block)
{
    // Here we assume that the generated loop will be embedded in a function where a "count" parameter is defined.
    string index = "i";

    // Generate code before the loop
    if (fPreInst->fCode.size() > 0) {
        block->pushBackInst(InstBuilder::genLabelInst("// Pre code"));
        block->pushBackInst(InstBuilder::genLabelInst("#pragma omp single"));
        pushBlock(fPreInst, block);
    }

    // Generate loop code
    if (fComputeInst->fCode.size() > 0) {
        DeclareVarInst* loop_init = InstBuilder::genDeclareVarInst(InstBuilder::genNamedAddress(index, Address::kLoop), InstBuilder::genBasicTyped(Typed::kInt), InstBuilder::genIntNumInst(0));
        ValueInst* loop_end = InstBuilder::genBinopInst(kLT,
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("count", Address::kStack)));
        StoreVarInst* loop_increment = InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(index, Address::kLoop),
                                            InstBuilder::genBinopInst(kAdd,
                                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                                    InstBuilder::genIntNumInst(1)));

        ForLoopInst* loop = InstBuilder::genForLoopInst(loop_init, loop_end, loop_increment);
        block->pushBackInst(InstBuilder::genLabelInst("// Compute code"));
        block->pushBackInst(InstBuilder::genLabelInst("#pragma omp for"));
        pushLoop(fComputeInst, loop);
        block->pushBackInst(loop);
    }

    // Generate code after the loop
    if (fPostInst->fCode.size() > 0) {
        block->pushBackInst(InstBuilder::genLabelInst("// Post code"));
        block->pushBackInst(InstBuilder::genLabelInst("#pragma omp single"));
        pushBlock(fPostInst, block);
    }
}

/**
 * A loop with recursive dependencies can't be run alone.
 * It must be included into another loop.
 * returns true is this loop has recursive dependencies
 * and must be included in an enclosing loop
 */
bool CodeLoop::hasRecDependencies()
{
    return !fRecDependencies.empty();
}

/**
 * Test if a loop is empty that is if it contains no lines of code.
 * @return true if the loop is empty
 */
bool CodeLoop::isEmpty()
{
    return fPreInst->fCode.empty() && fComputeInst->fCode.empty() && fPostInst->fCode.empty();
}

/**
 * Add a recursive dependency, unless it is itself
 */
void CodeLoop::addRecDependency(Tree t)
{
    if (t != fRecSymbol) {
        fRecDependencies.insert(t);
    }
}

/**
 * Search if t is defined in this loop
 * or the enclosing ones
 */
bool CodeLoop::findRecDefinition(Tree t)
{
    CodeLoop* l = this;
    while (l && l->fRecSymbol != t) l=l->fEnclosingLoop;
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
    assert(fSize == l->fSize);

    // update recursive dependencies by adding those from the absorbed loop
    fRecDependencies.insert(l->fRecDependencies.begin(), l->fRecDependencies.end());
    if (fIsRecursive) fRecDependencies.erase(fRecSymbol);

    // update loop dependencies by adding those from the absorbed loop
    fBackwardLoopDependencies.insert(l->fBackwardLoopDependencies.begin(), l->fBackwardLoopDependencies.end());

    // add the line of code of the absorbed loop
    fPreInst->fCode.insert(fPreInst->fCode.end(), l->fPreInst->fCode.begin(), l->fPreInst->fCode.end());
    fComputeInst->fCode.insert(fComputeInst->fCode.end(), l->fComputeInst->fCode.begin(), l->fComputeInst->fCode.end());
    fPostInst->fCode.insert(fPostInst->fCode.begin(), l->fPostInst->fCode.begin(), l->fPostInst->fCode.end());
}

void CodeLoop::concat(CodeLoop* l)
{
	//assert(l->fUseCount == 1);
	assert(fBackwardLoopDependencies.size() == 1);
	assert((*fBackwardLoopDependencies.begin()) == l);

	//fExtraLoops.push_front(l);
	fBackwardLoopDependencies = l->fBackwardLoopDependencies;
}

// Graph sorting

void CodeLoop::setOrder(CodeLoop* l, int order, lclgraph& V)
{
    assert(l);
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

void CodeLoop::resetOrder(CodeLoop* l)
{
    l->fOrder = -1;
    for (lclset::const_iterator p = l->fBackwardLoopDependencies.begin(); p != l->fBackwardLoopDependencies.end(); p++) {
        resetOrder(*p);
    }
}

void CodeLoop::sortGraph(CodeLoop* root, lclgraph& V)
{
    lclset T1, T2;
    int level;

    assert(root);
    resetOrder(root);
    T1.insert(root); level = 0; V.clear();
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
