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

#ifndef _FUNCTION_BUILDER_H
#define _FUNCTION_BUILDER_H

using namespace std;

#include <string.h>
#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "exception.hh"
#include "global.hh"
#include "instructions.hh"

/*
    void compute(int count, float** inputs, float** ouputs)
    {
        int toto = ....  (local var outside the loop)

        loop (....count....)
        {
            toto: use of var outside the loop

            field: kStruct variable

            float titi = ....  (local var inside the loop)
            loop_code
        }
    }

    ==> local var outside the loop : function parameter
    ==> var insided the loop : stay the same
    ==> "count" of the loop : function parameter
    ==> field: kStruct variable : stay the same
    ==> global variables : stay the same

    void extracted_loop(int toto, int count, .....)
    {
        loop (....count....)
        {
            toto: use of var from paramater list

            field: kStruct variable

            float titi = ....  (local var inside the loop)
            loop_code
        }
    }

    void extracted_loop(int count, float** inputs, float** ouputs)
    {
        call_loop(toto, count, ....)
    }

*/

struct Loop2FunctionBuider : public DispatchVisitor {
    // Variable management
    map<string, Address::AccessType> fLocalVarTable;
    list<string>                     fAddedVarTable;

    // Function definition creation
    Names fArgsTypeList;
    DeclareFunInst*   fFunctionDef;

    // Function call creation
    Values fArgsValueList;
    DropInst*        fFunctionCall;

    void createParameter(Address* address)
    {
        switch (address->getAccess()) {
            case Address::kStack:
            case Address::kLoop: {
                string name = address->getName();
                if (fLocalVarTable.find(name) == fLocalVarTable.end()) {
                    if (find(fAddedVarTable.begin(), fAddedVarTable.end(), name) ==
                        fAddedVarTable.end()) {  // First encounter

                        // Be sure variable is defined
                        // cerr << "createParameter kStack " << name << endl;
                        faustassert(gGlobal->gVarTypeTable.find(name) != gGlobal->gVarTypeTable.end());

                        // Local in the enclosing context, becomes a fun parameter
                        BasicCloneVisitor cloner;
                        fArgsTypeList.push_back(
                            InstBuilder::genNamedTyped(name, gGlobal->gVarTypeTable[name]->clone(&cloner)));

                        // It becomes a value in the fun-call argument list
                        fArgsValueList.push_back(InstBuilder::genLoadStackVar(name));

                        // Variable added in parameter list
                        fAddedVarTable.push_back(name);
                    }

                } else {
                    // Loop own local, nothing to do
                }
                break;
            }

            case Address::kFunArgs: {
                string name = address->getName();
                if (find(fAddedVarTable.begin(), fAddedVarTable.end(), name) ==
                    fAddedVarTable.end()) {  // First encounter

                    // Be sure variable is defined
                    // cerr << "createParameter kFunArgs " << name << endl;
                    faustassert(gGlobal->gVarTypeTable.find(name) != gGlobal->gVarTypeTable.end());

                    // Parameter in the enclosing function, becomes a fun parameter
                    BasicCloneVisitor cloner;
                    fArgsTypeList.push_back(
                        InstBuilder::genNamedTyped(name, gGlobal->gVarTypeTable[name]->clone(&cloner)));

                    // It becomes a value in the fun-call argument list : keep it's kFunArgs status
                    fArgsValueList.push_back(InstBuilder::genLoadFunArgsVar(name));

                    // Variable added in parameter list
                    fAddedVarTable.push_back(name);
                }
                break;
            }

            case Address::kStruct:
            case Address::kStaticStruct:
            case Address::kGlobal:
                // Nothing to do
                break;

            case Address::kLink:
                faustassert(false);
                break;

            default:
                break;
        }
    }

    virtual void visit(DeclareVarInst* inst)
    {
        DispatchVisitor::visit(inst);
        Address::AccessType access = inst->fAddress->getAccess();

        if (access == Address::kStack || access == Address::kLoop) {
            // Keep local variables in the loop
            fLocalVarTable[inst->fAddress->getName()] = access;
        }
    }

    virtual void visit(LoadVarInst* inst)
    {
        DispatchVisitor::visit(inst);
        createParameter(inst->fAddress);
    }

    virtual void visit(LoadVarAddressInst* inst) {}

    virtual void visit(StoreVarInst* inst)
    {
        DispatchVisitor::visit(inst);
        createParameter(inst->fAddress);
    }

    Loop2FunctionBuider(const string& fun_name, BlockInst* block, bool add_object = false)
    {
        // This prepare fArgsTypeList and fArgsValueList
        block->accept(this);

        // Change the status of all variables used in function parameter list
        struct LoopCloneVisitor : public BasicCloneVisitor {
            list<string>& fAddedVarTable;

            LoopCloneVisitor(list<string>& table) : fAddedVarTable(table) {}

            virtual Address* visit(NamedAddress* address)
            {
                if (find(fAddedVarTable.begin(), fAddedVarTable.end(), address->fName) != fAddedVarTable.end()) {
                    return InstBuilder::genNamedAddress(address->fName, Address::kFunArgs);
                } else {
                    return BasicCloneVisitor::visit(address);
                }
            }
        };

        // Put loop in new function
        LoopCloneVisitor cloner(fAddedVarTable);
        BlockInst*       function_code = static_cast<BlockInst*>(block->clone(&cloner));

        // Add a Ret (void) instruction (needed in LLVM backend)
        function_code->pushBackInst(InstBuilder::genRetInst());

        // Add "dsp" arg in function prototype and in parameter list
        if (add_object) {
            fArgsTypeList.push_front(InstBuilder::genNamedTyped("dsp", InstBuilder::genBasicTyped(Typed::kObj_ptr)));
            fArgsValueList.push_front(InstBuilder::genLoadFunArgsVar("dsp"));
        }

        // Create function
        fFunctionDef = InstBuilder::genVoidFunction(fun_name, fArgsTypeList, function_code);

        // Create function call
        fFunctionCall = InstBuilder::genDropInst(InstBuilder::genFunCallInst(fun_name, fArgsValueList));
    }
};

/*
Constant propagation :

1) changer des variables en constantes dans le code initial
2) cloner le code avec ConstantPropagationCloneVisitor
*/

struct ConstantPropagationBuilder : public BasicCloneVisitor {
    map<string, ValueInst*> fValueTable;

    virtual ValueInst* visit(BinopInst* inst)
    {
        ValueInst* val1 = inst->fInst1->clone(this);
        ValueInst* val2 = inst->fInst2->clone(this);

        FloatNumInst* float1 = dynamic_cast<FloatNumInst*>(val1);
        FloatNumInst* float2 = dynamic_cast<FloatNumInst*>(val2);

        // TODO
        Int32NumInst* int1 = dynamic_cast<Int32NumInst*>(val1);
        Int32NumInst* int2 = dynamic_cast<Int32NumInst*>(val2);

        // if (float1) float1->dump();
        // if (float2) float2->dump();

        if (float1 && float2) {
            switch (inst->fOpcode) {
                case kAdd:
                    return InstBuilder::genFloatNumInst(float1->fNum + float2->fNum);
                case kSub:
                    return InstBuilder::genFloatNumInst(float1->fNum - float2->fNum);
                case kMul:
                    return InstBuilder::genFloatNumInst(float1->fNum * float2->fNum);
                case kDiv:
                    return InstBuilder::genFloatNumInst(float1->fNum / float2->fNum);
                default:
                    return 0;
            }

        } else if (int1 && int2) {
            faustassert(false);
            return 0;
        } else {
            return InstBuilder::genBinopInst(inst->fOpcode, val1, val2);
        }
    }

    virtual ValueInst* visit(CastInst* inst)
    {
        ValueInst*    val1   = inst->fInst->clone(this);
        FloatNumInst* float1 = dynamic_cast<FloatNumInst*>(val1);
        Int32NumInst* int1   = dynamic_cast<Int32NumInst*>(val1);

        if (inst->fType->getType() == Typed::kFloat) {
            return (float1) ? float1 : InstBuilder::genFloatNumInst(float(int1->fNum));
        } else if (inst->fType->getType() == Typed::kInt32) {
            return (int1) ? int1 : InstBuilder::genInt32NumInst(int(float1->fNum));
        } else {
            faustassert(false);
            return 0;
        }
    }

    virtual ValueInst* visit(FunCallInst* inst)
    {
        Values cloned;
        for (const auto& it : inst->fArgs) {
            cloned.push_back(it->clone(this));
        }
        // TODO : si toute la liste des values sont des nombres, alors effectuer le calcul
        return InstBuilder::genFunCallInst(inst->fName, cloned, inst->fMethod);
    }

    virtual ValueInst* visit(Select2Inst* inst)
    {
        ValueInst*    val1   = inst->fCond->clone(this);
        FloatNumInst* float1 = dynamic_cast<FloatNumInst*>(val1);
        Int32NumInst* int1   = dynamic_cast<Int32NumInst*>(val1);

        if (float1) {
            return (float1->fNum > 0.f) ? inst->fThen->clone(this) : inst->fElse->clone(this);
        } else if (int1) {
            return (int1->fNum > 0) ? inst->fThen->clone(this) : inst->fElse->clone(this);
        } else {
            return InstBuilder::genSelect2Inst(val1, inst->fThen->clone(this), inst->fElse->clone(this));
        }
    }

    virtual StatementInst* visit(DeclareVarInst* inst)
    {
        ValueInst*    val1   = inst->fValue->clone(this);
        FloatNumInst* float1 = dynamic_cast<FloatNumInst*>(val1);
        Int32NumInst* int1   = dynamic_cast<Int32NumInst*>(val1);
        string        name   = inst->fAddress->getName();

        if (float1) {
            // float1->dump();
            // Creates a "link" so that corresponding load see the real value
            fValueTable[name] = float1;
            return InstBuilder::genDropInst();
        } else if (int1) {
            // Creates a "link" so that corresponding load see the real value
            fValueTable[name] = int1;
            return InstBuilder::genDropInst();
        } else {
            BasicCloneVisitor cloner;
            return InstBuilder::genDeclareVarInst(inst->fAddress->clone(&cloner), inst->fType->clone(&cloner), val1);
        }
    }

    virtual ValueInst* visit(LoadVarInst* inst)
    {
        string name = inst->fAddress->getName();
        if (fValueTable.find(name) != fValueTable.end()) {
            return fValueTable[name];
        } else {
            BasicCloneVisitor cloner;
            return InstBuilder::genLoadVarInst(inst->fAddress->clone(&cloner));
        }
    }

    virtual StatementInst* visit(StoreVarInst* inst)
    {
        ValueInst*    val1   = inst->fValue->clone(this);
        FloatNumInst* float1 = dynamic_cast<FloatNumInst*>(val1);
        Int32NumInst* int1   = dynamic_cast<Int32NumInst*>(val1);
        string        name   = inst->fAddress->getName();

        if (float1) {
            // float1->dump();
            // Creates a "link" so that corresponding load see the real value
            fValueTable[name] = float1;
            return InstBuilder::genDropInst();
        } else if (int1) {
            // Creates a "link" so that corresponding load see the real value
            fValueTable[name] = int1;
            return InstBuilder::genDropInst();
        } else {
            BasicCloneVisitor cloner;
            return InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner), val1);
        }
    }
};

#endif
