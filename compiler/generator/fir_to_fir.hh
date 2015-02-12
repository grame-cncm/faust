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

#ifndef _FIR_TO_FIR_H
#define _FIR_TO_FIR_H

#include "instructions.hh"
#include "code_container.hh"

#ifdef _WIN32
bool sortArrayDeclarations(StatementInst* a, StatementInst* b);
#else
bool sortArrayDeclarations(StatementInst* a, StatementInst* b);
#endif


// Change stack access for struct access
struct Stack2StructAnalyser : public DispatchVisitor {
    
    string fName;
    
    void visit(NamedAddress* address)
    {
        if (address->fAccess == Address::kStack && address->fName.find(fName) != string::npos) {
            address->fAccess = Address::kStruct;
        }
    }
    
    Stack2StructAnalyser(const string& name):fName(name)
    {}
};

// Analysis to promote stack variables to struct variables
struct Stack2StructAnalyser1 : public DispatchVisitor {
    
    CodeContainer* fContainer;
    string fName;
    
    // TODO : also rewrite value memory access
    void visit(DeclareVarInst* inst)
    {
        BasicCloneVisitor cloner;
        string name = inst->fAddress->getName();
        
        if (inst->fAddress->getAccess() == Address::kStack && name.find(fName) != string::npos) {
            
            // Variable moved to the Struct
            fContainer->pushDeclare(InstBuilder::genDecStructVar(name, inst->fType->clone(&cloner)));
            
            // For local thread access (in compute), rewrite the Declare instruction by a Store
            if (inst->fValue) {
                fContainer->pushComputeBlockMethod(InstBuilder::genStoreStructVar(name, inst->fValue->clone(&cloner)));
            }
            
            // Mark inst to be removed
            inst->fAddress->setAccess(Address::kLink);
        }
        
        // Then dispatch and possibly rewrite 'value' access
        DispatchVisitor::visit(inst);
    }
    
    void visit(NamedAddress* address)
    {
        if (address->fAccess == Address::kStack && address->fName.find(fName) != string::npos) {
            address->fAccess = Address::kStruct;
        }
    }
    
    Stack2StructAnalyser1(CodeContainer* container, const string& name)
        :fContainer(container), fName(name)
    {}
    
};

struct VariableMover {
    
    static void Move(CodeContainer* container, const string& name)
    {
        // Transform stack variables in struct variables
        Stack2StructAnalyser1 analyser1(container, name);
        container->generateComputeBlock(&analyser1);
        
        // Variable access stack ==> struct
        Stack2StructAnalyser analyser2(name);
        container->transformDAG(&analyser2);
    }
};

// Remove all variable declarations marked as "Address::kLink"
struct RemoverCloneVisitor : public BasicCloneVisitor {

    // Rewrite Declare as a no-op (DropInst)
    StatementInst* visit(DeclareVarInst* inst)
    {
        if (inst->fAddress->getAccess() == Address::kLink) {
            return new DropInst();
        } else {
            return BasicCloneVisitor::visit(inst);
        }
    }
};

#endif