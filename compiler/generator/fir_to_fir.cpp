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

#include <algorithm>

#include "fir_to_fir.hh"

using namespace std;

/*
 Sort arrays by size
*/

bool sortArrayDeclarations(StatementInst* a, StatementInst* b)
{
    DeclareVarInst* inst1 = dynamic_cast<DeclareVarInst*>(a);
    DeclareVarInst* inst2 = dynamic_cast<DeclareVarInst*>(b);

    if (inst1) {
        ArrayTyped* array_typed1 = dynamic_cast<ArrayTyped*>(inst1->fType);
        if (array_typed1) {
            if (inst2) {
                ArrayTyped* array_typed2 = dynamic_cast<ArrayTyped*>(inst2->fType);
                if (array_typed2) {
                    return (array_typed1->fSize == array_typed2->fSize)
                               ? (intptr_t)array_typed1 > (intptr_t)array_typed1
                               : array_typed1->fSize > array_typed2->fSize;
                }
            }
            return true;
        } else {
            return false;
        }
    } else if (inst2) {
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst2->fType);
        return (array_typed) ? (array_typed->fSize > 0) : false;
    } else {
        return false;
    }
}

/*
 Sort arrays by type : integer is moved first
 */

bool sortTypeDeclarations(StatementInst* a, StatementInst* b)
{
    DeclareVarInst* inst1 = dynamic_cast<DeclareVarInst*>(a);
    DeclareVarInst* inst2 = dynamic_cast<DeclareVarInst*>(b);

    if (inst1 && inst2) {
        return (inst1->fType->getType() == Typed::kInt32) || (inst1->fType->getType() == Typed::kInt32_ptr);
    } else {
        return false;
    }
}

// Inlining tools
// TODO: stack variables should be renamed since inlining the same function several times will create variables name clash

BlockInst* FunctionInliner::ReplaceParameterByArg(BlockInst* code, NamedTyped* named, ValueInst* arg)
{
    struct ValueInliner : public BasicCloneVisitor {
        NamedTyped*          fNamed;
        ValueInst*           fArg;
        map<string, string>& fVarTable;
        int                  fOccurence;
        
        ValueInliner(NamedTyped* named, ValueInst* arg, map<string, string>& table, int occurence)
        : fNamed(named), fArg(arg), fVarTable(table), fOccurence(occurence)
        {
        }
        
        Address* renameAddress(Address* dst_address, Address* src_address)
        {
            Address* cloned_dst_address = dst_address->clone(this);
            cloned_dst_address->setName(src_address->getName());
            cloned_dst_address->setAccess(src_address->getAccess());
            return cloned_dst_address;
        }
        
        ValueInst* visit(LoadVarInst* inst)
        {
            BasicCloneVisitor cloner;
            if (inst->fAddress->getName() == fNamed->fName) {
                if (fArg->isSimpleValue() || (fOccurence == 1)) {
                    return fArg->clone(&cloner);
                } else {
                    // More complex expressions are computed and shared in a new stack variable
                    if (fVarTable.find(fNamed->fName) == fVarTable.end()) {
                        // Create a stack variable with the value
                        string tmp_in            = gGlobal->getFreshID("tmp_in");
                        fVarTable[fNamed->fName] = tmp_in;
                        if (gGlobal->gHasTeeLocal) {
                            fBlockStack.top()->pushBackInst(
                                                            InstBuilder::genDecStackVar(tmp_in, fNamed->fType->clone(&cloner)));
                            return InstBuilder::genTeeVar(tmp_in, fArg->clone(&cloner));
                        } else {
                            fBlockStack.top()->pushBackInst(InstBuilder::genDecStackVar(
                                                                                        tmp_in, fNamed->fType->clone(&cloner), fArg->clone(&cloner)));
                            return InstBuilder::genLoadStackVar(tmp_in);
                        }
                    } else {
                        return InstBuilder::genLoadStackVar(fVarTable[fNamed->fName]);
                    }
                }
            } else {
                return inst->clone(&cloner);
            }
        }
        
        StatementInst* visit(StoreVarInst* inst)
        {
            LoadVarInst* arg;
            if ((inst->fAddress->getName() == fNamed->fName) && (arg = dynamic_cast<LoadVarInst*>(fArg))) {
                
                return InstBuilder::genStoreVarInst(renameAddress(inst->fAddress, arg->fAddress),
                                                    inst->fValue->clone(this));
            } else {
                return BasicCloneVisitor::visit(inst);
            }
        }
        
        BlockInst* getCode(BlockInst* src) { return static_cast<BlockInst*>(src->clone(this)); }
    };
    
    // Count variable load occurences in a block
    struct VariableLoadCounter : public DispatchVisitor {
        string fName;
        int    fOccurence;
        
        VariableLoadCounter(const string& name) : fName(name), fOccurence(0) {}
        
        virtual void visit(LoadVarInst* inst)
        {
            if (inst->fAddress->getName() == fName) {
                fOccurence++;
            }
        }
    };
    
    // Count variable occurence
    VariableLoadCounter counter(named->fName);
    code->accept(&counter);
    
    ValueInliner inliner(named, arg, fVarTable, counter.fOccurence);
    return inliner.getCode(code);
}

BlockInst* FunctionInliner::ReplaceParametersByArgs(BlockInst* code, list<NamedTyped*> args_type, list<ValueInst*> args,
                                                    bool ismethod)
{
    list<NamedTyped*>::iterator it1 = args_type.begin();
    list<ValueInst*>::iterator  it2 = args.begin();
    if (ismethod) { it2++; }
    
    for (; it1 != args_type.end(); it1++, it2++) {
        faustassert(it2 != args.end());
        code = ReplaceParameterByArg(code, *it1, *it2);
    }
    
    return code;
}

// Expand and rewrite ControlInst as 'IF (cond) {....}' instructions
void ControlExpander::beginCond(ControlInst* inst)
{
    faustassert(fIfBlockStack.top().fCond == nullptr);
    faustassert(fIfBlockStack.top().fIfInst == nullptr);
    
    fIfBlockStack.top().fCond = inst->fCond;
    fIfBlockStack.top().fIfInst = new IfInst(inst->fCond->clone(this), new BlockInst(), new BlockInst());
    fIfBlockStack.top().fIfInst->fThen->pushBackInst(inst->fStatement->clone(this));
}

void ControlExpander::continueCond(ControlInst* inst)
{
    faustassert(fIfBlockStack.top().fIfInst != nullptr);
    fIfBlockStack.top().fIfInst->fThen->pushBackInst(inst->fStatement->clone(this));
}

void ControlExpander::endCond()
{
    faustassert(fBlockStack.top() != nullptr);
 
    if (fIfBlockStack.size() > 0 && fIfBlockStack.top().fIfInst) {
        fBlockStack.top()->pushBackInst(fIfBlockStack.top().fIfInst);
        fIfBlockStack.top().init();
    }
}

StatementInst* ControlExpander::visit(ControlInst* inst)
{
    if (!fIfBlockStack.top().fCond) {
        beginCond(inst);
    } else if (inst->hasCondition(fIfBlockStack.top().fCond)) {
        continueCond(inst);
    } else {
        endCond();
        beginCond(inst);
    }
    
    // Not used
    return nullptr;
}

StatementInst* ControlExpander::visit(BlockInst* inst)
{
    BlockInst* cloned = new BlockInst();
    fBlockStack.push(cloned);
    
    fIfBlockStack.push(IfBlock());
    
    for (const auto& it : inst->fCode) {
        if (dynamic_cast<ControlInst*>(it)) {
            // ControlInst will progressively fill the current block by side effect
            it->clone(this);
        } else {
            endCond();
            cloned->pushBackInst(it->clone(this));
        }
    }
    
    // Possibly end last IF
    endCond();
    
    fBlockStack.pop();
    fIfBlockStack.pop();
    
    return cloned;
}
