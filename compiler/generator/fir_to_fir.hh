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
#include "fir_instructions.hh"

// Tool to dump FIR
inline void dump2FIR(StatementInst* inst, std::ostream* out = &cout)
{
    *out << "========== dump2FIR statement begin ==========" << std::endl;
    FIRInstVisitor fir_visitor(out);
    inst->accept(&fir_visitor);
    *out << "========== dump2FIR statement end ==========" << std::endl;
}

inline void dump2FIR(ValueInst* value, std::ostream* out = &cout)
{
    *out << "========== dump2FIR value begin ==========" << std::endl;
    FIRInstVisitor fir_visitor(out);
    value->accept(&fir_visitor);
    *out << "\n========== dump2FIR value end ==========" << std::endl;
}

bool sortArrayDeclarations(StatementInst* a, StatementInst* b);
bool sortTypeDeclarations(StatementInst* a, StatementInst* b);

// Change stack access for struct access
struct Stack2StructAnalyser : public DispatchVisitor {
    
    string fName;
    
	using DispatchVisitor::visit;

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
    
	using DispatchVisitor::visit;

    // TODO : also rewrite value memory access
    void visit(DeclareVarInst* inst)
    {
        BasicCloneVisitor cloner;
        string name = inst->fAddress->getName();
        
        if (inst->fAddress->getAccess() == Address::kStack && name.find(fName) != string::npos) {
            
            // Variable moved to the Struct
            fContainer->pushDeclare(InstBuilder::genDecStructVar(name, inst->fType->clone(&cloner)));
            
            // For local thread access (in compute), rewrite the Declare instruction by a Store and put in Init section
            if (inst->fValue) {
                fContainer->pushInitMethod(InstBuilder::genStoreStructVar(name, inst->fValue->clone(&cloner)));
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
            return InstBuilder::genDropInst();
        } else {
            return BasicCloneVisitor::visit(inst);
        }
    }
};

// Used in asm.js and WebAssembly backend

/*
 For subcontainers table generation : rename 'sig' in 'dsp' and remove 'dsp' allocation
 (using in ASMJavaScript and Interpreter backend)
*/

struct DspRenamer : public BasicCloneVisitor {
    
    DspRenamer()
    {}
    
    // Change access
    virtual Address* visit(NamedAddress* named)
    {
        if (startWith(named->getName(), "sig")) {
            return InstBuilder::genNamedAddress("dsp", named->fAccess);
        } else {
            return BasicCloneVisitor::visit(named);
        }
    }
    
    // Remove allocation
    virtual StatementInst* visit(DeclareVarInst* inst)
    {
        if (startWith(inst->fAddress->getName(), "sig")) {
            return InstBuilder::genDropInst();
        } else {
            BasicCloneVisitor cloner;
            return inst->clone(&cloner);
        }
    }
    
    BlockInst* getCode(BlockInst* src)
    {
        return dynamic_cast<BlockInst*>(src->clone(this));
    }
    
};

// Moves all variables declaration at the beginning of the block and rewrite them as 'declaration' followed by 'store'
struct MoveVariablesInFront2 : public BasicCloneVisitor {
    
    list<StatementInst*> fVarTable;
    
    virtual StatementInst* visit(DeclareVarInst* inst)
    {
        BasicCloneVisitor cloner;
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
        
        if (inst->fValue) {
            if (dynamic_cast<NumValueInst*>(inst->fValue)) {
                fVarTable.push_back(inst->clone(&cloner));
                return InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner), inst->fValue->clone(&cloner));
            // "In extension" array definition
            } else if (array_typed) {
                fVarTable.push_back(InstBuilder::genDeclareVarInst(inst->fAddress->clone(&cloner),
                                                                   inst->fType->clone(&cloner),
                                                                   InstBuilder::genTypedZero(inst->fType->getType())));
                Typed::VarType ctype = array_typed->fType->getType();
                if (array_typed->fSize > 0) {
                    if (ctype == Typed::kInt32) {
                        Int32ArrayNumInst* int_array = dynamic_cast<Int32ArrayNumInst*>(inst->fValue);
                        for (int i = 0; i < array_typed->fSize; i++) {
                            fVarTable.push_back(InstBuilder::genStoreArrayStaticStructVar(inst->fAddress->getName(),
                                                                                          InstBuilder::genInt32NumInst(i),
                                                                                          InstBuilder::genInt32NumInst(int_array->getValue(i))));
                        }
                    } else if (ctype == Typed::kFloat || ctype == Typed::kFloatMacro) {
                        FloatArrayNumInst* float_array = dynamic_cast<FloatArrayNumInst*>(inst->fValue);
                        for (int i = 0; i < array_typed->fSize; i++) {
                            fVarTable.push_back(InstBuilder::genStoreArrayStaticStructVar(inst->fAddress->getName(),
                                                                                          InstBuilder::genInt32NumInst(i),
                                                                                          InstBuilder::genFloatNumInst(float_array->getValue(i))));
                        }
                    } else if (ctype == Typed::kDouble) {
                        DoubleArrayNumInst* double_array = dynamic_cast<DoubleArrayNumInst*>(inst->fValue);
                        for (int i = 0; i < array_typed->fSize; i++) {
                            fVarTable.push_back(InstBuilder::genStoreArrayStaticStructVar(inst->fAddress->getName(),
                                                                                          InstBuilder::genInt32NumInst(i),
                                                                                          InstBuilder::genDoubleNumInst(double_array->getValue(i))));
                        }
                    } else {
                        faustassert(false);
                    }
                    return InstBuilder::genDropInst();
                } else {
                    return InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner), inst->fValue->clone(&cloner));
                }
            } else {
                fVarTable.push_back(InstBuilder::genDeclareVarInst(inst->fAddress->clone(&cloner),
                                                                   inst->fType->clone(&cloner),
                                                                   InstBuilder::genTypedZero(inst->fType->getType())));
                return InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner), inst->fValue->clone(&cloner));
            }
            
        } else {
            fVarTable.push_back(inst->clone(&cloner));
            return InstBuilder::genDropInst();
        }
    }
    
    BlockInst* getCode(BlockInst* src, bool local = false)
    {
        BlockInst* dst = dynamic_cast<BlockInst*>(src->clone(this));
        
        if (local) {
            // Separate with a list of pure DeclareVarInst (with no value), followed by a list of StoreVarInst
            BasicCloneVisitor cloner;
            list<StatementInst*> dec;
            list<StatementInst*> store;
            
            for (list<StatementInst*>::reverse_iterator it = fVarTable.rbegin(); it != fVarTable.rend(); ++it) {
                DeclareVarInst* dec_inst = dynamic_cast<DeclareVarInst*>(*it);
                StoreVarInst* store_inst = dynamic_cast<StoreVarInst*>(*it);
                if (dec_inst) {
                    dec.push_back(InstBuilder::genDeclareVarInst(dec_inst->fAddress->clone(&cloner), dec_inst->fType->clone(&cloner)));
                    store.push_back(InstBuilder::genStoreVarInst(dec_inst->fAddress->clone(&cloner), dec_inst->fValue->clone(&cloner)));
                } else if (store_inst) {
                    store.push_back(store_inst->clone(&cloner));
                } else {
                    faustassert(false);
                }
            }
            
            for (list<StatementInst*>::iterator it = store.begin(); it != store.end(); ++it) {
                dst->pushFrontInst(*it);
            }
            
            for (list<StatementInst*>::iterator it = dec.begin(); it != dec.end(); ++it) {
                dst->pushFrontInst(*it);
            }
        } else {
            // Separate with a list of DeclareVarInst with a value, followed by a list of StoreVarInst
            for (list<StatementInst*>::reverse_iterator it = fVarTable.rbegin(); it != fVarTable.rend(); ++it) {
                dst->pushFrontInst(*it);
            }
        }
        
        return dst;
    }
    
};

// Moves all variables declaration at the beginning of the block and rewrite them as 'declaration' followed by 'store'
struct MoveVariablesInFront3 : public BasicCloneVisitor {
    
    list<StatementInst*> fVarTableDeclaration;
    list<StatementInst*> fVarTableStore;
    
    virtual StatementInst* visit(DeclareVarInst* inst)
    {
        BasicCloneVisitor cloner;
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
        
        if (inst->fValue) {
            if (dynamic_cast<NumValueInst*>(inst->fValue)) {
                // Declaration rewriten as simple DeclareVarInst (without value) and a store
                fVarTableDeclaration.push_back(InstBuilder::genDeclareVarInst(inst->fAddress->clone(&cloner), inst->fType->clone(&cloner)));
                fVarTableStore.push_back(InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner), inst->fValue->clone(&cloner)));
                return InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner), inst->fValue->clone(&cloner));
                // "In extension" array definition
            } else if (array_typed) {
                fVarTableDeclaration.push_back(InstBuilder::genDeclareVarInst(inst->fAddress->clone(&cloner), inst->fType->clone(&cloner)));
                Typed::VarType ctype = array_typed->fType->getType();
                if (array_typed->fSize > 0) {
                    if (ctype == Typed::kInt32) {
                        Int32ArrayNumInst* int_array = dynamic_cast<Int32ArrayNumInst*>(inst->fValue);
                        for (int i = 0; i < array_typed->fSize; i++) {
                            fVarTableStore.push_back(InstBuilder::genStoreArrayStaticStructVar(inst->fAddress->getName(),
                                                                                          InstBuilder::genInt32NumInst(i),
                                                                                          InstBuilder::genInt32NumInst(int_array->getValue(i))));
                        }
                    } else if (ctype == Typed::kFloat || ctype == Typed::kFloatMacro) {
                        FloatArrayNumInst* float_array = dynamic_cast<FloatArrayNumInst*>(inst->fValue);
                        for (int i = 0; i < array_typed->fSize; i++) {
                            fVarTableStore.push_back(InstBuilder::genStoreArrayStaticStructVar(inst->fAddress->getName(),
                                                                                          InstBuilder::genInt32NumInst(i),
                                                                                          InstBuilder::genFloatNumInst(float_array->getValue(i))));
                        }
                    } else if (ctype == Typed::kDouble) {
                        DoubleArrayNumInst* double_array = dynamic_cast<DoubleArrayNumInst*>(inst->fValue);
                        for (int i = 0; i < array_typed->fSize; i++) {
                            fVarTableStore.push_back(InstBuilder::genStoreArrayStaticStructVar(inst->fAddress->getName(),
                                                                                          InstBuilder::genInt32NumInst(i),
                                                                                          InstBuilder::genDoubleNumInst(double_array->getValue(i))));
                        }
                    } else {
                        faustassert(false);
                    }
                    return InstBuilder::genDropInst();
                } else {
                    return InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner), inst->fValue->clone(&cloner));
                }
            } else {
                // Declaration rewriten as simple DeclareVarInst (without value) and a store
                fVarTableDeclaration.push_back(InstBuilder::genDeclareVarInst(inst->fAddress->clone(&cloner), inst->fType->clone(&cloner)));
                fVarTableStore.push_back(InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner), inst->fValue->clone(&cloner)));
                return InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner), inst->fValue->clone(&cloner));
            }
            
        } else {
            fVarTableDeclaration.push_back(dynamic_cast<DeclareVarInst*>(inst->clone(&cloner)));
            return InstBuilder::genDropInst();
        }
    }
    
    BlockInst* getCode(BlockInst* src)
    {
        BlockInst* dst = dynamic_cast<BlockInst*>(src->clone(this));
        // Variable store moved in front of block
        for (list<StatementInst*>::reverse_iterator it = fVarTableStore.rbegin(); it != fVarTableStore.rend(); ++it) {
            dst->pushFrontInst(*it);
        }
        // Then pure declaration
        for (list<StatementInst*>::reverse_iterator it = fVarTableDeclaration.rbegin(); it != fVarTableDeclaration.rend(); ++it) {
            dst->pushFrontInst(*it);
        }
        return dst;
    }
    
};

// Replace a void function call with the actual inlined function code

struct InlineVoidFunctionCall : public BasicCloneVisitor {
    
    DeclareFunInst* fFunction;
    
    InlineVoidFunctionCall(DeclareFunInst* function):fFunction(function)
    {}
    
    BlockInst* ReplaceParametersByArgs(BlockInst* code, list<NamedTyped*> args_type, list<ValueInst*> args, bool ismethod)
    {
        list<NamedTyped*>::iterator it1 = args_type.begin();
        list<ValueInst*>::iterator it2 = args.begin(); if (ismethod) { it2++; }
        
        for (; it1 != args_type.end(); it1++, it2++) {
            faustassert(it2 != args.end());
            code = ReplaceParameterByArg(code, *it1, *it2);
        }
        
        return code;
    }
    
    BlockInst* ReplaceParameterByArg(BlockInst* code, NamedTyped* type, ValueInst* arg)
    {
        struct InlineValue : public BasicCloneVisitor {
            
            string fName;
            ValueInst* fArg;
            string fInLoop;
    
            InlineValue(const string& name, ValueInst* arg):fName(name), fArg(arg), fInLoop("")
            {}
            
            Address* renameAddress(Address* address, const string& name)
            {
                Address* cloned_address = address->clone(this);
                cloned_address->setName(name);
                return cloned_address;
            }
            
            StatementInst* visit(DeclareVarInst* inst)
            {
                if (inst->fAddress->getAccess() == Address::kLoop) {
                    // Rename loop index with a fresh one
                    fInLoop = gGlobal->getFreshID("re_i");
                    return InstBuilder::genDeclareVarInst(renameAddress(inst->fAddress, fInLoop), inst->fType->clone(this), (inst->fValue) ? inst->fValue->clone(this) : NULL);
                } else {
                    return InstBuilder::genDeclareVarInst(inst->fAddress->clone(this), inst->fType->clone(this), (inst->fValue) ? inst->fValue->clone(this) : NULL);
                }
            }
            
            ValueInst* visit(LoadVarInst* inst)
            {
                if (inst->fAddress->getAccess() == Address::kLoop) {
                    // Rename loop index
                    return InstBuilder::genLoadVarInst(renameAddress(inst->fAddress, fInLoop));
                } else {
                    BasicCloneVisitor cloner;
                    return (inst->fAddress->getName() == fName) ? fArg->clone(&cloner) : inst->clone(&cloner);
                }
            }
            
            StatementInst* visit(StoreVarInst* inst)
            {
                LoadVarInst* arg;
                
                if ((inst->fAddress->getName() == fName) && (arg = dynamic_cast<LoadVarInst*>(fArg))) {
                    return InstBuilder::genStoreVarInst(renameAddress(inst->fAddress, arg->fAddress->getName()), inst->fValue->clone(this));
                } else if (inst->fAddress->getAccess() == Address::kLoop) {
                    // Rename loop index
                    return InstBuilder::genStoreVarInst(renameAddress(inst->fAddress, fInLoop), inst->fValue->clone(this));
                } else {
                    return InstBuilder::genStoreVarInst(inst->fAddress->clone(this), inst->fValue->clone(this));
                }
            }
            
            BlockInst* getCode(BlockInst* src)
            {
                return dynamic_cast<BlockInst*>(src->clone(this));
            }
        };
        
        InlineValue inliner(type->fName, arg);
        return inliner.getCode(code);
    }
    
    virtual StatementInst* visit(DropInst* inst)
    {
        FunCallInst* fun_call;
        if (inst->fResult
            && (fun_call = dynamic_cast<FunCallInst*>(inst->fResult))
            && (fun_call->fName == fFunction->fName)) {
            return ReplaceParametersByArgs(fFunction->fCode, fFunction->fType->fArgsTypes, fun_call->fArgs, fun_call->fMethod);
        } else {
            BasicCloneVisitor cloner;
            return inst->clone(&cloner);
        }
    }
   
    BlockInst* getCode(BlockInst* src)
    {
        return dynamic_cast<BlockInst*>(src->clone(this));
    }
};

#endif
