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

/**********************************************************************

		Historique :
		-----------

***********************************************************************/

using namespace std;

#include <string>
#include <list>
#include <set>
#include <map>
#include <vector>
#include <stack>

#include <iostream>
#include <sstream>
#include <algorithm>
#include <assert.h>
#include <string.h>

#include "instructions.hh"

/*
    void compute(int count, float** inputs, float** ouputs)
    {
        int toto = ....  (local var outside the loop)

        loop (....count....)
        {
            toto : use of var outside the loop

            field: kStruct variable

            float titi = ....  (local var inside the loop)
            loop_code
        }
    }

    ==> local var outside the loop : function parameter
    ==> var insided the loop : stay the same
    ==> "count" of the loop :  function parameter
    ==> field: kStruct variable : stay the same
    ==> global variables :  stay the same

    void extracted_loop(int toto, int count, .....)
    {
        loop (....count....)
        {
            toto : use of var from paramater list

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
                case Address::kLoop:
                    if (fLocalVarTable.find(address->getName()) == fLocalVarTable.end()) {

                        if (find(fAddedVarTable.begin(), fAddedVarTable.end(), address->getName()) == fAddedVarTable.end()) {  // First encounter

                            // Be sure variable is defined
                            //cerr << "createParameter kStack " << address->getName() << endl;
                            assert(gVarTable.find(address->getName()) != gVarTable.end());

                            // Local in the enclosing context, becomes a fun parameter
                            BasicCloneVisitor cloner;
                            fArgsTypeList.push_back(InstBuilder::genNamedTyped(address->getName(), gVarTable[address->getName()]->clone(&cloner)));

                            // It becomes a value in the fun-call argument list
                            fArgsValueList.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(address->getName(), Address::kStack)));

                            // Variable added in parameter list
                            fAddedVarTable.push_back(address->getName());
                        }

                    } else {
                        // Loop own local, nothing to do
                    }
                    break;

                case Address::kStruct:
                case Address::kStaticStruct:
                    // Nothing to do
                    break;

                case Address::kFunArgs:

                    if (find(fAddedVarTable.begin(), fAddedVarTable.end(), address->getName()) == fAddedVarTable.end()) {  // First encounter

                        // Be sure variable is defined
                        cerr << "createParameter kFunArgs " << address->getName() << endl;
                        assert(gVarTable.find(address->getName()) != gVarTable.end());

                        // Parameter in the enclosing function, becomes a fun parameter
                        BasicCloneVisitor cloner;
                        fArgsTypeList.push_back(InstBuilder::genNamedTyped(address->getName(), gVarTable[address->getName()]->clone(&cloner)));

                        // It becomes a value in the fun-call argument list : keep it's kFunArgs status
                        fArgsValueList.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(address->getName(), Address::kFunArgs)));

                        // Variable added in parameter list
                        fAddedVarTable.push_back(address->getName());
                    }
                    break;

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
                        return new NamedAddress(address->fName, Address::kFunArgs);
                    } else {
                        return BasicCloneVisitor::visit(address);
                    }
                }

            };

            // Put loop in new function
            LoopCloneVisitor cloner(fAddedVarTable);
            BlockInst* function_code = dynamic_cast<BlockInst*>(block->clone(&cloner));

            // Add a Ret (void) instruction
            function_code->pushBackInst(InstBuilder::genRetInst());

            // Add "dsp" arg in function prototype and in parameter list
            if (add_object) {
                fArgsTypeList.push_front(InstBuilder::genNamedTyped("dsp", InstBuilder::genBasicTyped(Typed::kObj_ptr)));
                fArgsValueList.push_front(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("dsp", Address::kFunArgs)));
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
            return new DropInst();
        } else {
            return BasicCloneVisitor::visit(inst);
        }
    }

    // Rewrite Load as an access to kept ValueInst
    ValueInst* visit(LoadVarInst* inst)
    {
        if (inst->fAddress->getAccess() == Address::kLink) {
            assert(fLinkTable.find(inst->fAddress->getName()) != fLinkTable.end());
            return fLinkTable[inst->fAddress->getName()]->clone(this);
        } else {
            return BasicCloneVisitor::visit(inst);
        }
    }

    // Rewrite Store as a no-op (DropInst)
    StatementInst* visit(StoreVarInst* inst)
    {
        if (inst->fAddress->getAccess() == Address::kLink) {
            return new DropInst();
        } else {
            return BasicCloneVisitor::visit(inst);
        }
    }

};

// Remove linked Declare/Load/Store with a given name family

struct StackVariableRemover : public DispatchVisitor {

    ForLoopInst* fResultLoop;

    // Table used to "link" direct Store and Load
    map<string, ValueInst*>  fLinkTable;

    // Store operation makes the "link" stuff
    struct VariableMarker : public DispatchVisitor {

        map<string, ValueInst*>&  fLinkTable;
        string fName;

        VariableMarker(map<string, ValueInst*>& linktable, const string& name)
            :fLinkTable(linktable),fName(name)
        {}

        virtual void visit(DeclareVarInst* inst)
        {
            DispatchVisitor::visit(inst);

            if (inst->fAddress->getAccess() == Address::kStack && inst->fAddress->getName().find(fName) != string::npos) {
                fLinkTable[inst->fAddress->getName()] = inst->fValue;
                inst->fAddress->setAccess(Address::kLink);
            }
        }

        virtual void visit(StoreVarInst* inst)
        {
            DispatchVisitor::visit(inst);

            if (inst->fAddress->getAccess() == Address::kStack && inst->fAddress->getName().find(fName) != string::npos) {
                fLinkTable[inst->fAddress->getName()] = inst->fValue;
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
 Here we assume that loops are "connected" buy "outputX  ==> inputX" like naming connection

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

            if (inst->fAddress->getName().find("output") != string::npos) {
                string link_name = "link" + inst->fAddress->getName().substr(strlen("output"), 0xFFFF);
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

            if (inst->fAddress->getName().find("input") != string::npos) {
                string link_name = "link" + inst->fAddress->getName().substr(strlen("input"), 0xFFFF);
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

        assert(fResultLoop);
        assert(loop3);

        // Insert code of second loop into first one
        // TODO
        assert(false);
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

1) changer des variales en constantes dans le code initial

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
        IntNumInst* int1 = dynamic_cast<IntNumInst*>(val1);
        IntNumInst* int2 = dynamic_cast<IntNumInst*>(val2);

        //if (float1) float1->dump();
        //if (float2) float2->dump();

        if (float1 && float2) {
            switch (inst->fOpcode) {
                case kAdd:
                    return new FloatNumInst(float1->fNum + float2->fNum);
                case kSub:
                    return new FloatNumInst(float1->fNum - float2->fNum);
                case kMul:
                    return new FloatNumInst(float1->fNum * float2->fNum);
                case kDiv:
                    return new FloatNumInst(float1->fNum / float2->fNum);
            }

        } else if (int1 && int2) {
            assert(false);
            //return new IntNumInst(inst->fOpcode(int1->fNum, int2->fNum));
        } else {
            return new BinopInst(inst->fOpcode, val1, val2);
        }
    }

    virtual ValueInst* visit(CastNumInst* inst)
    {
        ValueInst* val1 = inst->fInst->clone(this);
        FloatNumInst* float1 = dynamic_cast<FloatNumInst*>(val1);
        IntNumInst* int1 = dynamic_cast<IntNumInst*>(val1);

        if (inst->fTyped->getType() == Typed::kFloat) {
            return (float1) ? float1 : new FloatNumInst(float(int1->fNum));
        } else if (inst->fTyped->getType() == Typed::kInt) {
            return (int1) ? int1 : new IntNumInst(int(float1->fNum));
        } else {
            assert(false);
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
        return new FunCallInst(inst->fName, cloned, inst->fMethod);
    }

    virtual ValueInst* visit(Select2Inst* inst)
    {
        ValueInst* val1 = inst->fCond->clone(this);
        FloatNumInst* float1 = dynamic_cast<FloatNumInst*>(val1);
        IntNumInst* int1 = dynamic_cast<IntNumInst*>(val1);

        if (float1) {
            return (float1->fNum > 0.f) ? inst->fThen->clone(this) : inst->fElse->clone(this);
        } else if (int1) {
            return (int1->fNum > 0) ? inst->fThen->clone(this) : inst->fElse->clone(this);
        } else {
            return new Select2Inst(val1, inst->fThen->clone(this), inst->fElse->clone(this));
        }
    }

    virtual StatementInst* visit(DeclareVarInst* inst)
    {
        ValueInst* val1 = inst->fValue->clone(this);
        FloatNumInst* float1 = dynamic_cast<FloatNumInst*>(val1);
        IntNumInst* int1 = dynamic_cast<IntNumInst*>(val1);

        if (float1) {
            //float1->dump();
            // Creates a "link" so that corresponding load see the real value
            fValueTable[inst->fAddress->getName()] = float1;
            return new DropInst();
        } else if (int1) {
            // Creates a "link" so that corresponding load see the real value
            fValueTable[inst->fAddress->getName()] = int1;
            return new DropInst();
        } else {
            BasicCloneVisitor cloner;
            return new DeclareVarInst(inst->fAddress->clone(&cloner), inst->fTyped->clone(&cloner), val1);
        }
    }

    virtual ValueInst* visit(LoadVarInst* inst)
    {
        if (fValueTable.find(inst->fAddress->getName()) != fValueTable.end())  {
            return fValueTable[inst->fAddress->getName()];
        } else {
            BasicCloneVisitor cloner;
            return new LoadVarInst(inst->fAddress->clone(&cloner));
        }
    }

    virtual StatementInst* visit(StoreVarInst* inst)
    {
        ValueInst* val1 = inst->fValue->clone(this);

        FloatNumInst* float1 = dynamic_cast<FloatNumInst*>(val1);
        IntNumInst* int1 = dynamic_cast<IntNumInst*>(val1);

        if (float1) {
            //float1->dump();
            // Creates a "link" so that corresponding load see the real value
            fValueTable[inst->fAddress->getName()] = float1;
            return new DropInst();
        } else if (int1) {
            // Creates a "link" so that corresponding load see the real value
            fValueTable[inst->fAddress->getName()] = int1;
            return new DropInst();
        } else {
            BasicCloneVisitor cloner;
            return new StoreVarInst(inst->fAddress->clone(&cloner), val1);
        }
    }

};

/*

 Verificateur de code :

 - vérifier que les Load/Sore utilisent des variables bien définies

 - vérifier que les Funcall correspondent à des fonctions existantes

 - vérifier que les variables de boucles (kLoop) sont bien à l'intérieur d'une boucle de même variable

 - vérifier que les variable kStack sont bien utilisées dans un scope où elles sont définies

 - vérifier que les variables kFunArgs sont bien utilisées dans un scope où elles sont définies (à l'intéreur d'une fonction avec les bons arguments)

*/

struct CodeVerifier : public DispatchVisitor {

    typedef map <string, Address::AccessType> VarScope;

    map <string, FunTyped*> fFunctionTable;
    stack<VarScope> fStackVarsTable;
    VarScope fCurVarScope;

    CodeVerifier()
    {
        cout << "CodeVerifier" << std::endl;
    }
    virtual ~CodeVerifier()
    {}

    virtual void visit(DeclareVarInst* inst)
    {
        fCurVarScope[inst->fAddress->getName()] = inst->fAddress->getAccess();
        inst->fValue->accept(this);
    }

    virtual void visit(LoadVarInst* inst)
    {
        if (fCurVarScope.find(inst->fAddress->getName()) == fCurVarScope.end()) {

            Address::AccessType var_access = inst->fAddress->getAccess();

            switch (var_access) {

                case Address::kGlobal:
                case Address::kFunArgs:
                case Address::kStruct:
                case Address::kStaticStruct:
                    break;

                case Address::kStack:
                    cout << "Error load : stack variable " << inst->fAddress->getName() << " with no enclosing definition " << std::endl;
                    break;

                case Address::kLoop:
                    cout << "Error load : loop variable " << inst->fAddress->getName() << " with no enclosing loop " << std::endl;
                    break;

                case Address::kLink:
                    // TO CHECK
                    break;

                default:
                    break;
            }

        } else {

            Address::AccessType decl_access = fCurVarScope[inst->fAddress->getName()];
            Address::AccessType var_access = inst->fAddress->getAccess();

            switch (var_access) {

                case Address::kStruct:
                case Address::kStaticStruct:
                case Address::kFunArgs:
                case Address::kGlobal:
                    break;

                case Address::kStack:
                    if (decl_access != Address::kStack)
                        cout << "Error load : stack variable " << inst->fAddress->getName() << " with no enclosing definition " << std::endl;
                    break;

                case Address::kLoop:
                    if (decl_access != Address::kLoop)
                        cout << "Error load : loop variable " << inst->fAddress->getName() << " with no enclosing loop " << std::endl;
                    break;

                case Address::kLink:
                    // TO CHECK
                    break;

                default:
                    break;
            }
        }
    }

    virtual void visit(StoreVarInst* inst)
    {
        if (fCurVarScope.find(inst->fAddress->getName()) == fCurVarScope.end()) {

            Address::AccessType var_access = inst->fAddress->getAccess();

            switch (var_access) {

                case Address::kGlobal:
                case Address::kFunArgs:
                case Address::kStruct:
                case Address::kStaticStruct:
                    break;

                case Address::kStack:
                    cout << "Error store : stack variable " << inst->fAddress->getName() << " with no enclosing definition " << std::endl;
                    break;

                case Address::kLoop:
                    cout << "Error store : loop variable " << inst->fAddress->getName() << " with no enclosing loop " << std::endl;
                    break;

                case Address::kLink:
                    // TO CHECK
                    break;

                default:
                    break;
            }

        } else {

            Address::AccessType decl_access = fCurVarScope[inst->fAddress->getName()];
            Address::AccessType var_access = inst->fAddress->getAccess();

            switch (var_access) {

                case Address::kStruct:
                case Address::kStaticStruct:
                case Address::kFunArgs:
                case Address::kGlobal:
                    break;

                case Address::kStack:
                    if (decl_access != Address::kStack)
                        cout << "Error store : stack variable " << inst->fAddress->getName() << " with no enclosing definition " << std::endl;
                    break;

                case Address::kLoop:
                    if (decl_access != Address::kLoop)
                        cout << "Error store : loop variable " << inst->fAddress->getName() << " with no enclosing loop " << std::endl;
                    break;

                case Address::kLink:
                    // TO CHECK
                    break;

                default:
                    break;
            }
        }

        inst->fValue->accept(this);
    }

    virtual void visit(FunCallInst* inst)
    {
        if (fFunctionTable.find(inst->fName) == fFunctionTable.end()) {
             cout << "Error : function " << inst->fName << " not defined! " << std::endl;
        } else {
             FunTyped* type = fFunctionTable[inst->fName];
             if (type->fArgsTypes.size() != inst->fArgs.size()) {
                cout << "Error : function args list and actual args mismatch : args " << type->fArgsTypes.size() << " actual : " << inst->fArgs.size() << std::endl;
             }
        }
    }

    virtual void visit(DeclareFunInst* inst)
    {
        fFunctionTable[inst->fName] = inst->fType;

        // Keep current variable state, start an empty one
        fStackVarsTable.push(fCurVarScope);
        fCurVarScope.clear();

        // Function arguments pushed in the variable table
        list<NamedTyped*>::const_iterator it1;
        for (it1 = inst->fType->fArgsTypes.begin(); it1 != inst->fType->fArgsTypes.end(); it1++) {
           fCurVarScope[(*it1)->fName] = Address::kFunArgs;
        }

        inst->fCode->accept(this);

        // Restore old variable state
        fCurVarScope = fStackVarsTable.top();
        fStackVarsTable.pop();
    }

    virtual void visit(ForLoopInst* inst)
    {
        // Loop variable added in fCurVarScope
        inst->fInit->accept(this);
        inst->fEnd->accept(this);
        inst->fIncrement->accept(this);

        // Keep current variable state, start an empty one
        fStackVarsTable.push(fCurVarScope);
        fCurVarScope.clear();

        inst->fCode->accept(this);

        // Restore old variable state
        fCurVarScope = fStackVarsTable.top();
        fStackVarsTable.pop();
   }

};

// Specialize all simple kStruct variables with a given value

struct StructVarAnalyser : public DispatchVisitor {

    map<string, ValueInst*> fSpecializedValueTable;

    void visit(DeclareVarInst* inst)
    {
        DispatchVisitor::visit(inst);

        // Keep "simple" struct variables
        if (inst->fAddress->getAccess() == Address::kStruct && (dynamic_cast<BasicTyped*>(inst->fTyped) || dynamic_cast<NamedTyped*>(inst->fTyped))) {
            Typed::VarType type = inst->fTyped->getType();
            ValueInst* init;
            if (type == Typed::kFloat)
                init = InstBuilder::genFloatNumInst(0.5);
            else
                init = InstBuilder::genIntNumInst(1);
            fSpecializedValueTable[inst->fAddress->getName()] = init;
        }
    }
};

struct ControlSpecializer : public DispatchVisitor {

    StatementInst* fResultCode;

    // Mark all simple kStruct variables
    struct VariableMarker : public DispatchVisitor {

        map<string, ValueInst*>& fSpecializedValueTable;

        VariableMarker(map<string, ValueInst*>& valuetable)
            :fSpecializedValueTable(valuetable)
        {}

        void visit(StoreVarInst* inst)
        {
            DispatchVisitor::visit(inst);

            if (fSpecializedValueTable.find(inst->fAddress->getName()) != fSpecializedValueTable.end()) {
                inst->fAddress->setAccess(Address::kLink);
            } else {
                //cout << "ControlSpecializer StoreVarInst " << inst->fAddress->getName() << endl;
            }
        }

        void visit(LoadVarInst* inst)
        {
            DispatchVisitor::visit(inst);

            if (fSpecializedValueTable.find(inst->fAddress->getName()) != fSpecializedValueTable.end()) {
                inst->fAddress->setAccess(Address::kLink);
            } else {
                //cout << "ControlSpecializer LoadVarInst " << inst->fAddress->getName() << endl;
            }
        }
    };

    // To be used to clone the annotated code
    struct VariableSpecializer : public BasicCloneVisitor {

        map<string, ValueInst*>& fSpecializedValueTable;

        VariableSpecializer(map<string, ValueInst*>& valuetable)
            :fSpecializedValueTable(valuetable)
        {}

        // Rewrite Load as an access to kept ValueInst
        ValueInst* visit(LoadVarInst* inst)
        {
            if (inst->fAddress->getAccess() == Address::kLink) {
                assert(fSpecializedValueTable.find(inst->fAddress->getName()) != fSpecializedValueTable.end());
                return fSpecializedValueTable[inst->fAddress->getName()]->clone(this);
            } else {
                return BasicCloneVisitor::visit(inst);
            }
        }

        // Rewrite Store as a no-op (DropInst)
        StatementInst* visit(StoreVarInst* inst)
        {
            if (inst->fAddress->getAccess() == Address::kLink) {
                assert(fSpecializedValueTable.find(inst->fAddress->getName()) != fSpecializedValueTable.end());
                return new DropInst();
            } else {
                return BasicCloneVisitor::visit(inst);
            }
        }
    };

    ControlSpecializer(StatementInst* code, map<string, ValueInst*>& valuetable)
    {
        // Identify Store/Load with simple kStruct access
        VariableMarker marker(valuetable);
        code->accept(&marker);

        // Clone the code with specialized value
        VariableSpecializer specializer(valuetable);
        fResultCode = code->clone(&specializer);
    }

};

#endif
