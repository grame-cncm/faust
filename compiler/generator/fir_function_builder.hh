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

#ifndef _FUNCTION_BUILDER_H
#define _FUNCTION_BUILDER_H

using namespace std;

#include <string>
#include <list>
#include <map>
#include <vector>
#include <stack>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string.h>

#include "instructions.hh"
#include "global.hh"
#include "exception.hh"

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
    map <string, Address::AccessType> fLocalVarTable;
    list <string> fAddedVarTable;

    // Function definition creation
    list<NamedTyped*> fArgsTypeList;
    DeclareFunInst* fFunctionDef;

    // Function call creation
    list<ValueInst*> fArgsValueList;
    DropInst* fFunctionCall;

    void createParameter(Address* address)
    {
        switch(address->getAccess()) {

            case Address::kStack:
            case Address::kLoop: {
                string name = address->getName();
                if (fLocalVarTable.find(name) == fLocalVarTable.end()) {

                    if (find(fAddedVarTable.begin(), fAddedVarTable.end(), name) == fAddedVarTable.end()) {  // First encounter

                        // Be sure variable is defined
                        //cerr << "createParameter kStack " << name << endl;
                        faustassert(gGlobal->gVarTypeTable.find(name) != gGlobal->gVarTypeTable.end());

                        // Local in the enclosing context, becomes a fun parameter
                        BasicCloneVisitor cloner;
                        fArgsTypeList.push_back(InstBuilder::genNamedTyped(name, gGlobal->gVarTypeTable[name]->clone(&cloner)));

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
                if (find(fAddedVarTable.begin(), fAddedVarTable.end(), name) == fAddedVarTable.end()) {  // First encounter

                    // Be sure variable is defined
                    cout << "createParameter kFunArgs " << name << endl;
                    faustassert(gGlobal->gVarTypeTable.find(name) != gGlobal->gVarTypeTable.end());

                    // Parameter in the enclosing function, becomes a fun parameter
                    BasicCloneVisitor cloner;
                    fArgsTypeList.push_back(InstBuilder::genNamedTyped(name, gGlobal->gVarTypeTable[name]->clone(&cloner)));

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
                // TO CHECK
                break;

            default:
                break;
        }
    }

    virtual void visit(DeclareVarInst* inst)
    {
        DispatchVisitor::visit(inst);

        if (inst->fAddress->getAccess() == Address::kStack || inst->fAddress->getAccess() == Address::kLoop) {
            // Keep local variables in the loop
            fLocalVarTable[inst->fAddress->getName()] = inst->fAddress->getAccess();
        }
    }

    virtual void visit(LoadVarInst* inst)
    {
        DispatchVisitor::visit(inst);
        createParameter(inst->fAddress);
    }

    virtual void visit(LoadVarAddressInst* inst)
    {}

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

            list <string>& fAddedVarTable;

            LoopCloneVisitor(list <string>& table):fAddedVarTable(table)
            {}

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
        BlockInst* function_code = dynamic_cast<BlockInst*>(block->clone(&cloner));
        //BlockInst* function_code = InstBuilder::genBlockInst();

        // Add a Ret (void) instruction
        function_code->pushBackInst(InstBuilder::genRetInst());

        // Add "dsp" arg in function prototype and in parameter list
        if (add_object) {
            fArgsTypeList.push_front(InstBuilder::genNamedTyped("dsp", InstBuilder::genBasicTyped(Typed::kObj_ptr)));
            fArgsValueList.push_front(InstBuilder::genLoadFunArgsVar("dsp"));
        }

        // Create function type
        BasicTyped* result = InstBuilder::genBasicTyped(Typed::kVoid);
        FunTyped* fun_type = InstBuilder::genFunTyped(fArgsTypeList, result, FunTyped::kLocal);

        // Creates function definition
        fFunctionDef = InstBuilder::genDeclareFunInst(fun_name, fun_type, function_code);

        // Creates function call
        fFunctionCall = InstBuilder::genDropInst(InstBuilder::genFunCallInst(fun_name, fArgsValueList));
    }

};

// To be used to clone the annotated code
struct LoadStoreCloneVisitor : public BasicCloneVisitor {

    map<string, ValueInst*>&  fLinkTable;

    LoadStoreCloneVisitor(map<string, ValueInst*>& linktable)
        :fLinkTable(linktable)
    {}

    // Rewrite Declare as a no-op (DropInst)
    StatementInst* visit(DeclareVarInst* inst)
    {
        if (inst->fAddress->getAccess() == Address::kLink) {
            return InstBuilder::genDropInst();
        } else {
            return BasicCloneVisitor::visit(inst);
        }
    }

    // Rewrite Load as an access to kept ValueInst
    ValueInst* visit(LoadVarInst* inst)
    {
        if (inst->fAddress->getAccess() == Address::kLink) {
            string name = inst->fAddress->getName();
            faustassert(fLinkTable.find(name) != fLinkTable.end());
            return fLinkTable[name]->clone(this);
        } else {
            return BasicCloneVisitor::visit(inst);
        }
    }

    // Rewrite Store as a no-op (DropInst)
    StatementInst* visit(StoreVarInst* inst)
    {
        if (inst->fAddress->getAccess() == Address::kLink) {
            return InstBuilder::genDropInst();
        } else {
            return BasicCloneVisitor::visit(inst);
        }
    }

};

// Remove linked Declare/Load/Store with a given name family
struct StackVariableRemover : public DispatchVisitor {

    ForLoopInst* fResultLoop;

    // Table used to "link" direct Store and Load
    map<string, ValueInst*> fLinkTable;

    // Store operation makes the "link" stuff
    struct VariableMarker : public DispatchVisitor {

        map<string, ValueInst*>& fLinkTable;
        string fName;

        VariableMarker(map<string, ValueInst*>& linktable, const string& name)
            :fLinkTable(linktable),fName(name)
        {}

        virtual void visit(DeclareVarInst* inst)
        {
            DispatchVisitor::visit(inst);
            string name = inst->fAddress->getName();
            
            if (inst->fAddress->getAccess() == Address::kStack && name.find(fName) != string::npos) {
                fLinkTable[name] = inst->fValue;
                inst->fAddress->setAccess(Address::kLink);
            }
        }

        virtual void visit(StoreVarInst* inst)
        {
            DispatchVisitor::visit(inst);
            string name = inst->fAddress->getName();

            if (inst->fAddress->getAccess() == Address::kStack && name.find(fName) != string::npos) {
                fLinkTable[name] = inst->fValue;
                inst->fAddress->setAccess(Address::kLink);
            }
        }

        virtual void visit(LoadVarInst* inst)
        {
            DispatchVisitor::visit(inst);

            if (inst->fAddress->getAccess() == Address::kStack && inst->fAddress->getName().find(fName) != string::npos) {
                inst->fAddress->setAccess(Address::kLink);
            }
        }
    };

    // Warning : side effect on loop argument, provide a cloned version if needed
    StackVariableRemover(ForLoopInst* loop, const string& name)
    {
        // Identify Declare/Store/Load with name instructions and mark them as "links"
        VariableMarker marker(fLinkTable, name);
        loop->accept(&marker);

        // Clone the code of each loop, "linked" Declare/Store/Load are transformed : DeclareInst -> DropInst, StoreInst -> DropInst, LoadInst -> direct access to stored value
        LoadStoreCloneVisitor remover(fLinkTable);
        fResultLoop = dynamic_cast<ForLoopInst*>(loop->clone(&remover));
    }

};

// Remove linked Declare/Load/Store with a given name of name family
struct LLVMStackVariableRemover : public DispatchVisitor {

    ForLoopInst* fResultLoop;

    // Store operation makes the "link" stuff
    struct VariableMarker : public DispatchVisitor {

        string fName;

        VariableMarker(const string& name):fName(name)
        {}

        virtual void visit(DeclareVarInst* inst)
        {
            DispatchVisitor::visit(inst);

            if (inst->fAddress->getAccess() == Address::kStack && inst->fAddress->getName().find(fName) != string::npos) {
                inst->fAddress->setAccess(Address::kLink);
            }
        }

        virtual void visit(StoreVarInst* inst)
        {
            DispatchVisitor::visit(inst);

            if (inst->fAddress->getAccess() == Address::kStack && inst->fAddress->getName().find(fName) != string::npos) {
                inst->fAddress->setAccess(Address::kLink);
            }
        }

        virtual void visit(LoadVarInst* inst)
        {
            DispatchVisitor::visit(inst);

            if (inst->fAddress->getAccess() == Address::kStack && inst->fAddress->getName().find(fName) != string::npos) {
                inst->fAddress->setAccess(Address::kLink);
            }
        }
    };

    // Warning : side effect on loop argument, provide a cloned version if needed
    LLVMStackVariableRemover(ForLoopInst* loop, const string& name)
    {
        // Identify Declare/Store/Load with name instructions and mark them as "links"
        VariableMarker marker(name);
        loop->accept(&marker);

        BasicCloneVisitor remover;
        fResultLoop = dynamic_cast<ForLoopInst*>(loop->clone(&remover));
    }

    LLVMStackVariableRemover()
    {}

    void Mark(ForLoopInst* loop, const string& name)
    {
        VariableMarker marker(name);
        loop->accept(&marker);
    }

    void Finish(ForLoopInst* loop)
    {
        BasicCloneVisitor remover;
        fResultLoop = dynamic_cast<ForLoopInst*>(loop->clone(&remover));
    }
};

/*
 Sequence of "compatible" loops (that is : number of outputs of first is same as number of inputs of second)
 Here we assume that loops are "connected" by "outputX  ==> inputX" like naming connection

 1) links between outputs and inputs arrays are detected and inserted in the global fLinkTable (name, ValueInst)

 2) loop code is cloned:

    - each StoreInst is dropped (that is cloned as a DropInst instruction)
    - each LoadInst is replaced by the corresponding ValueInst kept in the fLinkTable for the given name

 3) then code of the second loop is included into the first one.

*/

struct SeqLoopBuilder : public DispatchVisitor {

    ForLoopInst* fResultLoop;

    // Table used to "link" direct Store and Load
    map<string, ValueInst*>  fLinkTable;

    // Store operation makes the "link" stuff
    struct FirstLoopVisitor : public DispatchVisitor {

        map<string, ValueInst*>&  fLinkTable;

        FirstLoopVisitor(map<string, ValueInst*>& linktable)
            :fLinkTable(linktable)
        {}

        virtual void visit(StoreVarInst* inst)
        {
            DispatchVisitor::visit(inst);
            string name = inst->fAddress->getName();

            if (name.find("output") != string::npos) {
                string link_name = "link" + name.substr(strlen("output"), 0xFFFF);
                fLinkTable[link_name] = inst->fValue;
                inst->fAddress->setAccess(Address::kLink);
                inst->fAddress->setName(link_name);
            }
        }
    };

    // Load operation sees the "link" stuff
    struct SecondLoopVisitor : public DispatchVisitor {

        map<string, ValueInst*>&  fLinkTable;

        SecondLoopVisitor(map<string, ValueInst*>& linktable)
            :fLinkTable(linktable)
        {}

        virtual void visit(LoadVarInst* inst)
        {
            DispatchVisitor::visit(inst);
            string name = inst->fAddress->getName();
            
            if (name.find("input") != string::npos) {
                string link_name = "link" + name.substr(strlen("input"), 0xFFFF);
                inst->fAddress->setAccess(Address::kLink);
                inst->fAddress->setName(link_name);
            }
        }
    };

    // Warning : side effect on loop1 and loop2 arguments, provide a cloned version if needed
    SeqLoopBuilder(ForLoopInst* loop1, ForLoopInst* loop2)
    {
        // Identify Store "output" like instructions and mark them as "link" Store
        FirstLoopVisitor first_loop(fLinkTable);
        loop1->accept(&first_loop);

        // Identify Load "input" like instructions and mark them as "link" Load
        SecondLoopVisitor second_loop(fLinkTable);
        loop2->accept(&second_loop);

        // Clone the code of each loop, "linked" Store/Load are transformed : StoreInst -> DropInst, LoadInst -> direct access to stored value
        LoadStoreCloneVisitor remover(fLinkTable);
        fResultLoop = dynamic_cast<ForLoopInst*>(loop1->clone(&remover));
        ForLoopInst* loop3 = dynamic_cast<ForLoopInst*>(loop2->clone(&remover));

        faustassert(fResultLoop);
        faustassert(loop3);

        // Insert code of second loop into first one
        // TODO
        faustassert(false);
        /*
        list<StatementInst*>::const_iterator it;
        for (it = loop3->fCode.begin(); it != loop3->fCode.end(); it++) {
            fResultLoop->fCode.push_back(*it);
        }
        */
    }

    virtual ~SeqLoopBuilder()
    {}

};

// Parallel of loops

struct ParLoopBuilder : public DispatchVisitor {

    StatementInst* fFunction_def1;
    StatementInst* fFunction_def2;

    ParLoopBuilder(ForLoopInst* loop1, ForLoopInst* loop2)
    {}

    virtual ~ParLoopBuilder()
    {}
};

/*
Constant propagation :

1) changer des variables en constantes dans le code initial
2) cloner le code avec ConstantPropagationCloneVisitor

*/

struct ConstantPropagationBuilder : public BasicCloneVisitor {

    map <string, ValueInst*> fValueTable;

    virtual ValueInst* visit(BinopInst* inst)
    {
        ValueInst* val1 = inst->fInst1->clone(this);
        ValueInst* val2 = inst->fInst2->clone(this);

        FloatNumInst* float1 = dynamic_cast<FloatNumInst*>(val1);
        FloatNumInst* float2 = dynamic_cast<FloatNumInst*>(val2);

        // TODO
        Int32NumInst* int1 = dynamic_cast<Int32NumInst*>(val1);
        Int32NumInst* int2 = dynamic_cast<Int32NumInst*>(val2);

        //if (float1) float1->dump();
        //if (float2) float2->dump();

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
            //return new Int32NumInst(inst->fOpcode(int1->fNum, int2->fNum));
        } else {
            return InstBuilder::genBinopInst(inst->fOpcode, val1, val2);
        }
    }

    virtual ValueInst* visit(CastInst* inst)
    {
        ValueInst* val1 = inst->fInst->clone(this);
        FloatNumInst* float1 = dynamic_cast<FloatNumInst*>(val1);
        Int32NumInst* int1 = dynamic_cast<Int32NumInst*>(val1);

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
        list<ValueInst*> cloned;
        list<ValueInst*>::const_iterator it;
        for (it = inst->fArgs.begin(); it != inst->fArgs.end(); it++) {
            cloned.push_back((*it)->clone(this));
        }
        // TODO : si toute la liste des values sont des nombres, alors effectuer le calcul
        return InstBuilder::genFunCallInst(inst->fName, cloned, inst->fMethod);
    }

    virtual ValueInst* visit(Select2Inst* inst)
    {
        ValueInst* val1 = inst->fCond->clone(this);
        FloatNumInst* float1 = dynamic_cast<FloatNumInst*>(val1);
        Int32NumInst* int1 = dynamic_cast<Int32NumInst*>(val1);

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
        ValueInst* val1 = inst->fValue->clone(this);
        FloatNumInst* float1 = dynamic_cast<FloatNumInst*>(val1);
        Int32NumInst* int1 = dynamic_cast<Int32NumInst*>(val1);
        string name = inst->fAddress->getName();

        if (float1) {
            //float1->dump();
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
        if (fValueTable.find(name) != fValueTable.end())  {
            return fValueTable[name];
        } else {
            BasicCloneVisitor cloner;
            return InstBuilder::genLoadVarInst(inst->fAddress->clone(&cloner));
        }
    }

    virtual StatementInst* visit(StoreVarInst* inst)
    {
        ValueInst* val1 = inst->fValue->clone(this);
        FloatNumInst* float1 = dynamic_cast<FloatNumInst*>(val1);
        Int32NumInst* int1 = dynamic_cast<Int32NumInst*>(val1);
        string name = inst->fAddress->getName();

        if (float1) {
            //float1->dump();
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
