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

#ifndef _FIR_CODE_CHECKER_H
#define _FIR_CODE_CHECKER_H

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

 Code checker:

 - check that Load/Store only use defined variables
 - check that Load use initialized variables (either with a Declaration or a Store)
 - check that Funcall match with defined functions
 - check that loop variables (kLoop) are correctly inside a loop with the same variable name
 - check that kStack variables are only used in a their scope (and not outside)
 - check that kFunArgs variables are only used in a scope where they are defined (within a function with the correct
 arguments)
 - check Load/Store access coherency (among 'struct', 'stack', 'loop'...)

*/

struct FIRCodeChecker : public DispatchVisitor {
    typedef std::map<std::string, std::pair<Address::AccessType, bool> > VarScope;

    std::map<std::string, FunTyped*> fFunctionTable;
    std::vector<VarScope>  fStackVarsTable;
    VarScope               fCurVarScope;
    int                    fError;

    FIRCodeChecker() : fError(0)
    {
        // cout << "CodeVerifier" << std::endl;
    }
    virtual ~FIRCodeChecker() {}

    void printScope(VarScope scope)
    {
        VarScope::iterator it;
        std::cout << "----printScope----" << std::endl;
        for (it = scope.begin(); it != scope.end(); it++) {
            std::cout << "Variable : " << (*it).first << std::endl;
        }
    }

    bool getVarName(const std::string& name, std::pair<Address::AccessType, bool>& res)
    {
        // cout << "----getVarName : " << name << " ----" << endl;
        // printScope(fCurVarScope);

        if (fCurVarScope.find(name) != fCurVarScope.end()) {
            // cout << "Variable \"" << name << "\" found in current scope" << std::endl;
            res = fCurVarScope[name];
            return true;
        } else {
            std::vector<VarScope>::reverse_iterator rit;
            int scope_num = 1;
            for (rit = fStackVarsTable.rbegin(); rit < fStackVarsTable.rend(); ++rit, scope_num++) {
                VarScope scope = *rit;
                // cout << "SCOPE : "  << scope_num << std::endl;
                // printScope(scope);
                if (scope.find(name) != scope.end()) {
                    // cout << "getVarName Variable \"" << name << "\" found in scope " << scope_num << std::endl;
                    res = scope[name];
                    return true;
                }
            }

            return false;
        }
    }

    bool setVarName(const std::string& name)
    {
        // cout << "----setVarName : " << name << " ----" << endl;
        // printScope(fCurVarScope);

        if (fCurVarScope.find(name) != fCurVarScope.end()) {
            // cout << "Variable \"" << name << "\" found in current scope" << std::endl;
            fCurVarScope[name].second = true;
            // cout << "setVarName Variable \"" << name << "\" found in CURRENT scope " << std::endl;
            return true;
        } else {
            std::vector<VarScope>::reverse_iterator rit;
            int                                scope_num = 1;
            for (rit = fStackVarsTable.rbegin(); rit < fStackVarsTable.rend(); ++rit, scope_num++) {
                // VarScope scope = *rit;
                // cout << "SCOPE : "  << scope_num << std::endl;
                // printScope(scope);
                if ((*rit).find(name) != (*rit).end()) {
                    (*rit)[name].second = true;
                    // cout << "setVarName Variable \"" << name << "\" found in scope " << scope_num << std::endl;
                    return true;
                }
            }
            // cout << "setVarName Variable \"" << name << "\" NOT found in scope " << scope_num << std::endl;
            return false;
        }
    }

    virtual void visit(DeclareVarInst* inst)
    {
        std::string name         = inst->fAddress->getName();
        fCurVarScope[name].first = inst->fAddress->getAccess();

        if (inst->fValue) {
            inst->fValue->accept(this);
            // variable is initialized...
            fCurVarScope[name].second = true;
            // cout << "DeclareVarInst Variable \"" << name << "\" SET VALUE" << std::endl;
        } else {
            // variable is not initialized...
            fCurVarScope[name].second = false;
            // cout << "DeclareVarInst Variable \"" << name << "\"" << std::endl;
        }
    }

    virtual void visit(LoadVarInst* inst)
    {
        std::pair<Address::AccessType, bool> var_def;
        std::string name = inst->fAddress->getName();
        bool res = getVarName(name, var_def);

        if (!res) {
            if (inst->fAddress->getAccess() != Address::kFunArgs) {
                std::cout << "Error load : " << Address::dumpString(inst->fAddress->getAccess()) << " variable \"" << name
                     << "\" with no enclosing definition" << std::endl;
                fError++;
            }
        } else {
            if (!var_def.second && inst->fAddress->getAccess() != Address::kFunArgs) {
                std::cout << "Error load : variable \"" << name << "\" not initialized !!" << std::endl;
                fError++;
            }
            if (var_def.first != inst->fAddress->getAccess()) {
                std::cout << "Error load : incoherency in variable access \"" << name << "\"" << std::endl;
                fError++;
            }
        }
    }

    virtual void visit(LoadVarAddressInst* inst)
    {
        std::pair<Address::AccessType, bool> var_def;
        std::string name = inst->fAddress->getName();
        bool res = getVarName(name, var_def);

        if (!res) {
            if (inst->fAddress->getAccess() != Address::kFunArgs) {
                std::cout << "Error load : " << Address::dumpString(inst->fAddress->getAccess()) << " variable \"" << name
                     << "\" with no enclosing definition" << std::endl;
                fError++;
            }
        } else {
            if (var_def.first != inst->fAddress->getAccess()) {
                std::cout << "Error load : incoherency in variable access \"" << name << "\"" << std::endl;
                fError++;
            }
        }
    }

    virtual void visit(StoreVarInst* inst)
    {
        std::pair<Address::AccessType, bool> var_def;
        std::string name = inst->fAddress->getName();
        bool res = getVarName(name, var_def);

        if (!res) {
            std::cout << "Error store : " << Address::dumpString(inst->fAddress->getAccess()) << " variable \"" << name
                 << "\" with no enclosing definition" << std::endl;
            fError++;
        } else {
            if (var_def.first != inst->fAddress->getAccess()) {
                std::cout << "Error store : incoherency in variable access \"" << name << "\"" << std::endl;
                fError++;
            }
        }

        inst->fValue->accept(this);
        // variable is initialized...
        setVarName(name);
    }

    virtual void visit(FunCallInst* inst)
    {
        if (fFunctionTable.find(inst->fName) == fFunctionTable.end()) {
            std::cout << "Error : function \"" << inst->fName << "\" not defined! " << std::endl;
        } else {
            FunTyped* type = fFunctionTable[inst->fName];
            if (type->fArgsTypes.size() != inst->fArgs.size()) {
                std::cout << "Error : function args list and actual args mismatch : args " << type->fArgsTypes.size()
                     << " actual : " << inst->fArgs.size() << std::endl;
                fError++;
            }
        }
    }

    virtual void visit(DeclareFunInst* inst)
    {
        fFunctionTable[inst->fName] = inst->fType;

        // Function arguments pushed in the variable table
        Names::const_iterator it1;
        for (it1 = inst->fType->fArgsTypes.begin(); it1 != inst->fType->fArgsTypes.end(); it1++) {
            fCurVarScope[(*it1)->fName].first = Address::kFunArgs;
        }

        // Internal will start a new scope of variables
        inst->fCode->accept(this);
    }

    virtual void visit(ForLoopInst* inst)
    {
        // cout << "visit(ForLoopInst* inst) " << endl;
        // printScope(fCurVarScope);

        // Keep current variable state, start an empty one
        fStackVarsTable.push_back(fCurVarScope);
        fCurVarScope.clear();

        // Variable definition in a new scope...
        inst->fInit->accept(this);
        inst->fIncrement->accept(this);
        inst->fEnd->accept(this);

        // And block is a new scope...
        inst->fCode->accept(this);

        // Restore old variable state
        fCurVarScope = fStackVarsTable.back();
        fStackVarsTable.pop_back();
    }

    virtual void visit(BlockInst* inst)
    {
        // cout << "visit(BlockInst* inst) " << endl;
        // printScope(fCurVarScope);

        // Keep current variable state, start an empty one
        fStackVarsTable.push_back(fCurVarScope);
        fCurVarScope.clear();

        std::list<StatementInst*>::const_iterator it;
        for (it = inst->fCode.begin(); it != inst->fCode.end(); it++) {
            (*it)->accept(this);
        }

        // Restore old variable state
        fCurVarScope = fStackVarsTable.back();
        fStackVarsTable.pop_back();
    }
};

// Specialize all simple kStruct variables with a given value
struct StructVarAnalyser : public DispatchVisitor {
    std::map<std::string, ValueInst*> fSpecializedValueTable;

    void visit(DeclareVarInst* inst)
    {
        DispatchVisitor::visit(inst);

        // Keep "simple" struct variables
        if (inst->fAddress->getAccess() == Address::kStruct &&
            (dynamic_cast<BasicTyped*>(inst->fType) || dynamic_cast<NamedTyped*>(inst->fType))) {
            Typed::VarType type = inst->fType->getType();
            ValueInst*     init;
            if (type == Typed::kFloat) {
                init = InstBuilder::genFloatNumInst(0.5);
            } else {
                init = InstBuilder::genInt32NumInst(1);
            }
            fSpecializedValueTable[inst->fAddress->getName()] = init;
        }
    }
};

struct ControlSpecializer : public DispatchVisitor {
    StatementInst* fResultCode;

    // Mark all simple kStruct variables
    struct VariableMarker : public DispatchVisitor {
        std::map<std::string, ValueInst*>& fSpecializedValueTable;

        VariableMarker(std::map<std::string, ValueInst*>& valuetable) : fSpecializedValueTable(valuetable) {}

        void visit(StoreVarInst* inst)
        {
            DispatchVisitor::visit(inst);

            if (fSpecializedValueTable.find(inst->fAddress->getName()) != fSpecializedValueTable.end()) {
                inst->fAddress->setAccess(Address::kLink);
            } else {
                // cout << "ControlSpecializer StoreVarInst " << inst->fAddress->getName() << endl;
            }
        }

        void visit(LoadVarInst* inst)
        {
            DispatchVisitor::visit(inst);

            if (fSpecializedValueTable.find(inst->fAddress->getName()) != fSpecializedValueTable.end()) {
                inst->fAddress->setAccess(Address::kLink);
            } else {
                // cout << "ControlSpecializer LoadVarInst " << inst->fAddress->getName() << endl;
            }
        }
    };

    // To be used to clone the annotated code
    struct VariableSpecializer : public BasicCloneVisitor {
        std::map<std::string, ValueInst*>& fSpecializedValueTable;

        VariableSpecializer(std::map<std::string, ValueInst*>& valuetable) : fSpecializedValueTable(valuetable) {}

        // Rewrite Load as an access to kept ValueInst
        ValueInst* visit(LoadVarInst* inst)
        {
            std::string name = inst->fAddress->getName();
            if (inst->fAddress->getAccess() == Address::kLink) {
                faustassert(fSpecializedValueTable.find(name) != fSpecializedValueTable.end());
                return fSpecializedValueTable[name]->clone(this);
            } else {
                return BasicCloneVisitor::visit(inst);
            }
        }

        // Rewrite Store as a no-op (DropInst)
        StatementInst* visit(StoreVarInst* inst)
        {
            if (inst->fAddress->getAccess() == Address::kLink) {
                faustassert(fSpecializedValueTable.find(inst->fAddress->getName()) != fSpecializedValueTable.end());
                return InstBuilder::genDropInst();
            } else {
                return BasicCloneVisitor::visit(inst);
            }
        }
    };

    ControlSpecializer(StatementInst* code, std::map<std::string, ValueInst*>& valuetable)
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
