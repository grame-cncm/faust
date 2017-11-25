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

#ifndef _FIR_CODE_CHECKER_H
#define _FIR_CODE_CHECKER_H

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

 Verificateur de code :

 - vérifier que les Load/Store utilisent des variables bien définies
 - vérifier que les Load utilisent des variables bien initialiées (soit par une Declaration ou un Store prealable)
 - vérifier que les Funcall correspondent à des fonctions existantes
 - vérifier que les variables de boucles (kLoop) sont bien à l'intérieur d'une boucle de même nom de variable
 - vérifier que les variables kStack sont bien utilisées dans un scope où elles sont définies (et pas en dehors)
 - vérifier que les variables kFunArgs sont bien utilisées dans un scope où elles sont définies (à l'intérieur d'une fonction avec les bons arguments)
 - vérifier la cohérence des accès Load/Store (entre 'struct', 'stack', 'loop'...)

*/

struct FIRCodeChecker: public DispatchVisitor {

    typedef map <string, pair <Address::AccessType, bool> > VarScope;

    map <string, FunTyped*> fFunctionTable;
    vector<VarScope> fStackVarsTable;
    VarScope fCurVarScope;
    int fError;

    FIRCodeChecker():fError(0)
    {
        //cout << "CodeVerifier" << std::endl;
    }
    virtual ~FIRCodeChecker()
    {}
    
    void printScope(VarScope scope)
    {
        VarScope::iterator it;
        cout << "----printScope----" << endl;
        for (it = scope.begin(); it != scope.end(); it++) {
            cout << "Variable : " << (*it).first << endl;
        }
    }

    bool getVarName(const string& name, pair <Address::AccessType, bool>& res) 
    {
        //cout << "----getVarName : " << name << " ----" << endl;
        //printScope(fCurVarScope);
         
        if (fCurVarScope.find(name) != fCurVarScope.end()) {
            //cout << "Variable \"" << name << "\" found in current scope" << std::endl;
            res = fCurVarScope[name];
            return true;
        } else {
            vector<VarScope>::reverse_iterator rit; 
            int scope_num = 1;
            for (rit = fStackVarsTable.rbegin(); rit < fStackVarsTable.rend(); ++rit, scope_num++) {
                VarScope scope = *rit;
                //cout << "SCOPE : "  << scope_num << std::endl;
                //printScope(scope);
                if (scope.find(name) != scope.end()) {
                    //cout << "getVarName Variable \"" << name << "\" found in scope " << scope_num << std::endl;
                    res = scope[name];
                    return true;
                }
            }
            
            return false;
        }
    }
    
    bool setVarName(const string& name) 
    {
        //cout << "----setVarName : " << name << " ----" << endl;
        //printScope(fCurVarScope);
         
        if (fCurVarScope.find(name) != fCurVarScope.end()) {
            //cout << "Variable \"" << name << "\" found in current scope" << std::endl;
            fCurVarScope[name].second = true;
            //cout << "setVarName Variable \"" << name << "\" found in CURRENT scope " << std::endl;
            return true;
        } else {
            vector<VarScope>::reverse_iterator rit; 
            int scope_num = 1;
            for (rit = fStackVarsTable.rbegin(); rit < fStackVarsTable.rend(); ++rit, scope_num++) {
                //VarScope scope = *rit;
                //cout << "SCOPE : "  << scope_num << std::endl;
                //printScope(scope);
                if ((*rit).find(name) != (*rit).end()) {
                    (*rit)[name].second = true;
                    //cout << "setVarName Variable \"" << name << "\" found in scope " << scope_num << std::endl;
                    return true;
                }
            }
            //cout << "setVarName Variable \"" << name << "\" NOT found in scope " << scope_num << std::endl;
            return false;
        }
    }

    virtual void visit(DeclareVarInst* inst)
    {
        string name = inst->fAddress->getName();
        fCurVarScope[name].first = inst->fAddress->getAccess();
       
        if (inst->fValue) {
            inst->fValue->accept(this);
            // variable is initialized...
            fCurVarScope[name].second = true;
            //cout << "DeclareVarInst Variable \"" << name << "\" SET VALUE" << std::endl;
        } else {
            // variable is not initialized...
            fCurVarScope[name].second = false;
            //cout << "DeclareVarInst Variable \"" << name << "\"" << std::endl;
        }
    }
    
    virtual void visit(LoadVarInst* inst)
    {
        pair <Address::AccessType, bool> var_def;
        string name = inst->fAddress->getName();
        bool res = getVarName(name, var_def);
        
        if (!res) {
            if (inst->fAddress->getAccess() != Address::kFunArgs) {
                cout << "Error load : " << Address::dumpString(inst->fAddress->getAccess()) << " variable \"" << name << "\" with no enclosing definition" << std::endl;
                fError++;
            }
        } else {
            if (!var_def.second && inst->fAddress->getAccess() != Address::kFunArgs) {
                cout << "Error load : variable \"" << name << "\" not initialized !!" << std::endl;
                fError++;
            }
            if (var_def.first != inst->fAddress->getAccess()) {
                cout << "Error load : incoherency in variable access \"" << name << "\"" << std::endl;
                fError++;
            }
        }
    }
    
    virtual void visit(LoadVarAddressInst* inst)
    {
        pair <Address::AccessType, bool> var_def;
        string name = inst->fAddress->getName();
        bool res = getVarName(name, var_def);
        
        if (!res) {
            if (inst->fAddress->getAccess() != Address::kFunArgs) {
                cout << "Error load : " << Address::dumpString(inst->fAddress->getAccess()) << " variable \"" << name << "\" with no enclosing definition" << std::endl;
                fError++;
            }
        } else {
            if (var_def.first != inst->fAddress->getAccess()) {
                cout << "Error load : incoherency in variable access \"" << name << "\"" << std::endl;
                fError++;
            }
        }
    }
   
    virtual void visit(StoreVarInst* inst)
    {
        pair <Address::AccessType, bool> var_def;
        string name = inst->fAddress->getName();
        bool res = getVarName(name, var_def);
        
        if (!res) {
            cout << "Error store : " << Address::dumpString(inst->fAddress->getAccess()) << " variable \"" << name << "\" with no enclosing definition" << std::endl;
            fError++;
        } else {
            if (var_def.first != inst->fAddress->getAccess()) {
                cout << "Error store : incoherency in variable access \"" << name << "\"" << std::endl;
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
             cout << "Error : function \"" << inst->fName << "\" not defined! " << std::endl;
        } else {
             FunTyped* type = fFunctionTable[inst->fName];
             if (type->fArgsTypes.size() != inst->fArgs.size()) {
                cout << "Error : function args list and actual args mismatch : args " << type->fArgsTypes.size() << " actual : " << inst->fArgs.size() << std::endl;
                fError++;
             }
        }
    }

    virtual void visit(DeclareFunInst* inst)
    {
        fFunctionTable[inst->fName] = inst->fType;

        // Function arguments pushed in the variable table
        list<NamedTyped*>::const_iterator it1;
        for (it1 = inst->fType->fArgsTypes.begin(); it1 != inst->fType->fArgsTypes.end(); it1++) {
           fCurVarScope[(*it1)->fName].first = Address::kFunArgs;
        }

        // Internal will start a new scope of variables
        inst->fCode->accept(this);
    }
    
    virtual void visit(ForLoopInst* inst)
    {
        //cout << "visit(ForLoopInst* inst) " << endl;
        //printScope(fCurVarScope);
        
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
        //cout << "visit(BlockInst* inst) " << endl;
        //printScope(fCurVarScope);
        
         // Keep current variable state, start an empty one
        fStackVarsTable.push_back(fCurVarScope);
        fCurVarScope.clear();
        
        list<StatementInst*>::const_iterator it;
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

    map<string, ValueInst*> fSpecializedValueTable;

    void visit(DeclareVarInst* inst)
    {
        DispatchVisitor::visit(inst);

        // Keep "simple" struct variables
        if (inst->fAddress->getAccess() == Address::kStruct && (dynamic_cast<BasicTyped*>(inst->fType) || dynamic_cast<NamedTyped*>(inst->fType))) {
            Typed::VarType type = inst->fType->getType();
            ValueInst* init;
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
            string name = inst->fAddress->getName();
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
