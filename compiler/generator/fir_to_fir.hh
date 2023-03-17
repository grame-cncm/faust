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

#ifndef _FIR_TO_FIR_H
#define _FIR_TO_FIR_H

#include <stack>

#include "code_container.hh"
#include "fir_instructions.hh"
#include "instructions.hh"
#include "typing_instructions.hh"

// Tools to dump FIR
inline void dump2FIR(StatementInst* inst, std::ostream& out = std::cerr, bool complete = true)
{
    std::stringstream str;
    if (complete) str << "========== dump2FIR " << inst << " statement begin ========== " << std::endl;
    FIRInstVisitor fir_visitor(&str);
    inst->accept(&fir_visitor);
    if (complete) str << "========== dump2FIR statement end ==========" << std::endl;
    out << str.str();
}

inline void dump2FIR(ValueInst* value, std::ostream& out = std::cerr, bool complete = true)
{
    std::stringstream str;
    if (complete) str << "========== dump2FIR " << value << " value begin ========== " << std::endl;
    FIRInstVisitor fir_visitor(&str);
    value->accept(&fir_visitor);
    if (complete) str << "\n========== dump2FIR value end ==========" << std::endl;
    out << str.str();
}

inline void dump2FIR(Address* address, std::ostream& out = std::cerr, bool complete = true)
{
    std::stringstream str;
    if (complete) str << "========== dump2FIR " << address << " address begin ========== " << std::endl;
    FIRInstVisitor fir_visitor(&str);
    address->accept(&fir_visitor);
    if (complete) str << "\n========== dump2FIR address end ==========" << std::endl;
    out << str.str();
}

inline void dump2FIR(Typed* type, std::ostream& out = std::cerr, bool complete = true)
{
    std::stringstream str;
    if (complete) str << "========== dump2FIR " << type << " type begin ========== " << std::endl;
    FIRInstVisitor fir_visitor(&str);
    str << fir_visitor.generateType(type);
    if (complete) str << "\n========== dump2FIR type end ==========" << std::endl;
    out << str.str();
}

bool sortArrayDeclarations(StatementInst* a, StatementInst* b);
bool sortTypeDeclarations(StatementInst* a, StatementInst* b);

// Analysis to change stack access to struct access
struct Stack2StructRewriter1 : public DispatchVisitor {
    std::string fName;

    using DispatchVisitor::visit;

    void visit(NamedAddress* address)
    {
        if (address->fAccess == Address::kStack && address->fName.find(fName) != std::string::npos) {
            address->fAccess = Address::kStruct;
        }
    }

    Stack2StructRewriter1(const std::string& name) : fName(name) {}
};

// Analysis to promote stack variables to struct variables
struct Stack2StructRewriter2 : public DispatchVisitor {
    CodeContainer* fContainer;
    std::string   fName;

    using DispatchVisitor::visit;

    void visit(DeclareVarInst* inst)
    {
        BasicCloneVisitor cloner;
        std::string       name = inst->fAddress->getName();

        if (inst->fAddress->getAccess() == Address::kStack && name.find(fName) != std::string::npos) {
            // Variable moved to the Struct
            fContainer->pushDeclare(InstBuilder::genDecStructVar(name, inst->fType->clone(&cloner)));

            // For local thread access (in compute):
            // - rewrite the Declare instruction by a Store and put in Init section
            // - rewrite value access
            if (inst->fValue) {
                // Rewrite value access before cloning it
                Stack2StructRewriter1 rewriter(name);
                inst->fValue->accept(&rewriter);
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
        if (address->fAccess == Address::kStack && address->fName.find(fName) != std::string::npos) {
            address->fAccess = Address::kStruct;
        }
    }

    Stack2StructRewriter2(CodeContainer* container, const std::string& name) : fContainer(container), fName(name) {}
};

struct VariableMover {
    static void Move(CodeContainer* container, const std::string& name)
    {
        // Transform stack variables in struct variables
        Stack2StructRewriter2 rewriter2(container, name);
        container->generateComputeBlock(&rewriter2);

        // Rewrite variable access stack ==> struct
        Stack2StructRewriter1 rewriter1(name);
        container->transformDAG(&rewriter1);
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

// ========================================
// Used in WebAssembly and Interp backends
// ========================================

/*
 For subcontainers table generation : rename 'sig' in 'dsp' and remove 'dsp' allocation.
*/

struct DspRenamer : public BasicCloneVisitor {
    DspRenamer() {}

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
            return BasicCloneVisitor::visit(inst);
        }
    }

};

// Moves all variables declaration at the beginning of the block and rewrite them as 'declaration' followed by 'store'
struct MoveVariablesInFront2 : public BasicCloneVisitor {
    std::list<StatementInst*> fVarTable;

    virtual StatementInst* visit(DeclareVarInst* inst)
    {
        BasicCloneVisitor cloner;
        ArrayTyped*       array_typed = dynamic_cast<ArrayTyped*>(inst->fType);

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
                        if (int_array) {
                            for (int i = 0; i < array_typed->fSize; i++) {
                                fVarTable.push_back(InstBuilder::genStoreArrayStaticStructVar(
                                    inst->fAddress->getName(), InstBuilder::genInt32NumInst(i),
                                    InstBuilder::genInt32NumInst(int_array->getValue(i))));
                            }
                        } else {
                            return InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner),
                                                                inst->fValue->clone(&cloner));
                        }
                    } else if (ctype == Typed::kFloat || ctype == Typed::kFloatMacro) {
                        FloatArrayNumInst* float_array = dynamic_cast<FloatArrayNumInst*>(inst->fValue);
                        if (float_array) {
                            for (int i = 0; i < array_typed->fSize; i++) {
                                fVarTable.push_back(InstBuilder::genStoreArrayStaticStructVar(
                                    inst->fAddress->getName(), InstBuilder::genInt32NumInst(i),
                                    InstBuilder::genFloatNumInst(float_array->getValue(i))));
                            }
                        } else {
                            return InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner),
                                                                inst->fValue->clone(&cloner));
                        }
                    } else if (ctype == Typed::kDouble) {
                        DoubleArrayNumInst* double_array = dynamic_cast<DoubleArrayNumInst*>(inst->fValue);
                        if (double_array) {
                            for (int i = 0; i < array_typed->fSize; i++) {
                                fVarTable.push_back(InstBuilder::genStoreArrayStaticStructVar(
                                    inst->fAddress->getName(), InstBuilder::genInt32NumInst(i),
                                    InstBuilder::genDoubleNumInst(double_array->getValue(i))));
                            }
                        } else {
                            return InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner),
                                                                inst->fValue->clone(&cloner));
                        }
                    } else if (ctype == Typed::kFixedPoint) {
                        FixedPointArrayNumInst* fixed_array = dynamic_cast<FixedPointArrayNumInst*>(inst->fValue);
                        if (fixed_array) {
                            for (int i = 0; i < array_typed->fSize; i++) {
                                fVarTable.push_back(InstBuilder::genStoreArrayStaticStructVar(
                                  inst->fAddress->getName(), InstBuilder::genInt32NumInst(i),
                                  InstBuilder::genCastInst(InstBuilder::genFixedPointNumInst(fixed_array->getValue(i)), fixed_array->fType)));
                                
                            }
                        } else {
                            return InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner),
                                                                inst->fValue->clone(&cloner));
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
            fVarTable.push_back(InstBuilder::genDeclareVarInst(inst->fAddress->clone(&cloner),
                                                               inst->fType->clone(&cloner),
                                                               InstBuilder::genTypedZero(inst->fType->getType())));
            return InstBuilder::genDropInst();
        }
    }

    BlockInst* getCode(BlockInst* src, bool local = false)
    {
        BlockInst* dst = static_cast<BlockInst*>(src->clone(this));

        if (local) {
            // Separate with a list of pure DeclareVarInst (with no value), followed by a list of StoreVarInst
            BasicCloneVisitor    cloner;
            std::list<StatementInst*> dec;
            std::list<StatementInst*> store;

            for (std::list<StatementInst*>::reverse_iterator it = fVarTable.rbegin(); it != fVarTable.rend(); ++it) {
                DeclareVarInst* dec_inst   = dynamic_cast<DeclareVarInst*>(*it);
                StoreVarInst*   store_inst = dynamic_cast<StoreVarInst*>(*it);
                if (dec_inst) {
                    dec.push_back(InstBuilder::genDeclareVarInst(dec_inst->fAddress->clone(&cloner),
                                                                 dec_inst->fType->clone(&cloner)));
                    store.push_back(InstBuilder::genStoreVarInst(dec_inst->fAddress->clone(&cloner),
                                                                 dec_inst->fValue->clone(&cloner)));
                } else if (store_inst) {
                    store.push_back(store_inst->clone(&cloner));
                } else {
                    faustassert(false);
                }
            }

            for (const auto& it : store) {
                dst->pushFrontInst(it);
            }

            for (const auto& it : dec) {
                dst->pushFrontInst(it);
            }
        } else {
            // Separate with a list of DeclareVarInst with a value, followed by a list of StoreVarInst
            for (std::list<StatementInst*>::reverse_iterator it = fVarTable.rbegin(); it != fVarTable.rend(); ++it) {
                dst->pushFrontInst(*it);
            }
        }

        return dst;
    }
};

// Moves all variables declaration at the beginning of the block and rewrite them as 'declaration' followed by 'store'
struct MoveVariablesInFront3 : public BasicCloneVisitor {
    std::list<StatementInst*> fVarTableDeclaration;
    std::list<StatementInst*> fVarTableStore;

    virtual StatementInst* visit(DeclareVarInst* inst)
    {
        BasicCloneVisitor cloner;
        ArrayTyped*       array_typed = dynamic_cast<ArrayTyped*>(inst->fType);

        if (inst->fValue) {
            if (dynamic_cast<NumValueInst*>(inst->fValue)) {
                // Declaration rewriten as simple DeclareVarInst (without value) and a store
                fVarTableDeclaration.push_back(
                    InstBuilder::genDeclareVarInst(inst->fAddress->clone(&cloner), inst->fType->clone(&cloner)));
                fVarTableStore.push_back(
                    InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner), inst->fValue->clone(&cloner)));
                return InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner), inst->fValue->clone(&cloner));
                // "In extension" array definition
            } else if (array_typed) {
                fVarTableDeclaration.push_back(
                    InstBuilder::genDeclareVarInst(inst->fAddress->clone(&cloner), inst->fType->clone(&cloner)));
                Typed::VarType ctype = array_typed->fType->getType();
                if (array_typed->fSize > 0) {
                    if (ctype == Typed::kInt32) {
                        Int32ArrayNumInst* int_array = dynamic_cast<Int32ArrayNumInst*>(inst->fValue);
                        if (int_array) {
                            for (int i = 0; i < array_typed->fSize; i++) {
                                fVarTableStore.push_back(InstBuilder::genStoreArrayStaticStructVar(
                                    inst->fAddress->getName(), InstBuilder::genInt32NumInst(i),
                                    InstBuilder::genInt32NumInst(int_array->getValue(i))));
                            }
                        } else {
                            return InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner),
                                                                inst->fValue->clone(&cloner));
                        }
                    } else if (ctype == Typed::kFloat || ctype == Typed::kFloatMacro) {
                        FloatArrayNumInst* float_array = dynamic_cast<FloatArrayNumInst*>(inst->fValue);
                        if (float_array) {
                            for (int i = 0; i < array_typed->fSize; i++) {
                                fVarTableStore.push_back(InstBuilder::genStoreArrayStaticStructVar(
                                    inst->fAddress->getName(), InstBuilder::genInt32NumInst(i),
                                    InstBuilder::genFloatNumInst(float_array->getValue(i))));
                            }
                        } else {
                            return InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner),
                                                                inst->fValue->clone(&cloner));
                        }
                    } else if (ctype == Typed::kDouble) {
                        DoubleArrayNumInst* double_array = dynamic_cast<DoubleArrayNumInst*>(inst->fValue);
                        if (double_array) {
                            for (int i = 0; i < array_typed->fSize; i++) {
                                fVarTableStore.push_back(InstBuilder::genStoreArrayStaticStructVar(
                                    inst->fAddress->getName(), InstBuilder::genInt32NumInst(i),
                                    InstBuilder::genDoubleNumInst(double_array->getValue(i))));
                            }
                        } else {
                            return InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner),
                                                                inst->fValue->clone(&cloner));
                        }
                    } else if (ctype == Typed::kFixedPoint) {
                        FixedPointArrayNumInst* fixed_array = dynamic_cast<FixedPointArrayNumInst*>(inst->fValue);
                        if (fixed_array) {
                            for (int i = 0; i < array_typed->fSize; i++) {
                                fVarTableStore.push_back(InstBuilder::genStoreArrayStaticStructVar(
                                   inst->fAddress->getName(), InstBuilder::genInt32NumInst(i),
                                   InstBuilder::genCastInst(InstBuilder::genFixedPointNumInst(fixed_array->getValue(i)), fixed_array->fType)));
                            }
                        } else {
                            return InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner),
                                                                inst->fValue->clone(&cloner));
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
                fVarTableDeclaration.push_back(
                    InstBuilder::genDeclareVarInst(inst->fAddress->clone(&cloner), inst->fType->clone(&cloner)));
                fVarTableStore.push_back(
                    InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner), inst->fValue->clone(&cloner)));
                return InstBuilder::genStoreVarInst(inst->fAddress->clone(&cloner), inst->fValue->clone(&cloner));
            }

        } else {
            fVarTableDeclaration.push_back(dynamic_cast<DeclareVarInst*>(inst->clone(&cloner)));
            return InstBuilder::genDropInst();
        }
    }

    BlockInst* getCode(BlockInst* src)
    {
        BlockInst* dst = static_cast<BlockInst*>(src->clone(this));
        // Variable store moved in front of block
        for (std::list<StatementInst*>::reverse_iterator it = fVarTableStore.rbegin(); it != fVarTableStore.rend(); ++it) {
            dst->pushFrontInst(*it);
        }
        // Then pure declaration
        for (std::list<StatementInst*>::reverse_iterator it = fVarTableDeclaration.rbegin();
             it != fVarTableDeclaration.rend(); ++it) {
            dst->pushFrontInst(*it);
        }
        return dst;
    }
};

/*
 Rename loop variable and all access (warning: does not work with nested loops with the same variable name...)
 */
struct LoopVariableRenamer : public BasicCloneVisitor {
  
    std::map<std::string, std::string> fLoopIndexMap;
    
    virtual StatementInst* visit(DeclareVarInst* inst)
    {
        // Rename 'loop' variables
        if (dynamic_cast<NamedAddress*>(inst->fAddress) && inst->fAddress->getAccess() == Address::kLoop) {
            std::string name = inst->fAddress->getName();
            fLoopIndexMap[name] = gGlobal->getFreshID(name + "_re");
        }
        return BasicCloneVisitor::visit(inst);
    }
    
    virtual Address* visit(NamedAddress* address)
    {
        if (address->fAccess == Address::kLoop && fLoopIndexMap.find(address->getName()) != fLoopIndexMap.end()) {
            return InstBuilder::genNamedAddress(fLoopIndexMap[address->getName()], address->fAccess);
        } else {
            return BasicCloneVisitor::visit(address);
        }
    }
    
};

// ===============
// Inlining tools
// ===============

// TODO: stack variables should be renamed since inlining the same function several times will create variables name clash

struct FunctionInliner {
    std::map<std::string, std::string> fVarTable;

    BlockInst* ReplaceParameterByArg(BlockInst* code, NamedTyped* named, ValueInst* arg);
    BlockInst* ReplaceParametersByArgs(BlockInst* code, Names args_type, Values args, bool ismethod);
};

// Replace a function call with the actual inlined function code
struct FunctionCallInliner : public BasicCloneVisitor {
    
    DeclareFunInst* fFunction;

    FunctionCallInliner(DeclareFunInst* function) : fFunction(function) {}

    virtual ValueInst* visit(FunCallInst* inst)
    {
        FunCallInst* fun_call = inst;
        if (fun_call->fName == fFunction->fName) {
            FunctionInliner inliner;
            BlockInst*      inlined = inliner.ReplaceParametersByArgs(fFunction->fCode, fFunction->fType->fArgsTypes,
                                                                 fun_call->fArgs, fun_call->fMethod);
            
            // Get return value and remove it from the block
            ValueInst* res = inlined->getReturnValue();
            // Put the code without the value into the enclosing block
            fBlockStack.top()->pushBackInst(inlined);
            return res;
        } else {
            return BasicCloneVisitor::visit(inst);
        }
    }

};

// Compute the size in bytes of variables of a given type
struct VariableSizeCounter : public DispatchVisitor {
    
    int                 fSizeBytes;
    Typed::VarType      fType;
    Address::AccessType fAccess;

    VariableSizeCounter(Address::AccessType access, Typed::VarType type = Typed::kNoType)
    {
        fSizeBytes = 0;
        fType      = type;
        fAccess    = access;
    }

    virtual void visit(DeclareVarInst* inst)
    {
        DispatchVisitor::visit(inst);

        if (((fType == Typed::kNoType) || (inst->fType->getType() == fType)) && inst->fAddress->getAccess() | fAccess) {
            fSizeBytes += inst->fType->getSizeBytes();
        }
    }
};

// Remove unneeded cast
struct CastRemover : public BasicCloneVisitor {
    
    virtual ValueInst* visit(::CastInst* inst)
    {
        Typed::VarType value_type = TypingVisitor::getType(inst->fInst);
        Typed::VarType cast_type = inst->fType->getType();

        if (isInt32Type(cast_type)) {
            if (isInt32Type(value_type)) {
                //std::cerr << "CastInst : cast to int, but arg already int !" << std::endl;
                //dump2FIR(inst);
                return inst->fInst->clone(this);
            } else {
                /*
                // TODO = protection out-of [INT32_MIN, INT32_MAX] range
                ValueInst* max = InstBuilder::genRealNumInst(Typed::kFloat, double(std::numeric_limits<int>::max()));
                ValueInst* min = InstBuilder::genRealNumInst(Typed::kFloat, double(std::numeric_limits<int>::min()));
                
                return InstBuilder::genSelect2Inst(InstBuilder::genGreater(inst->fInst->clone(this), max),
                                                   InstBuilder::genInt32NumInst(std::numeric_limits<int>::max()),
                                                   InstBuilder::genSelect2Inst(InstBuilder::genLess(inst->fInst->clone(this), min),
                                                                               InstBuilder::genInt32NumInst(std::numeric_limits<int>::min()),
                                                                               BasicTypingCloneVisitor::visit(inst)));
                */
                return BasicCloneVisitor::visit(inst);
            }
        } else if (isRealType(cast_type)) {
            if (isRealType(value_type)) {
                //std::cerr << "CastInst : cast to real, but arg already real !" << std::endl;
                //dump2FIR(inst);
                return inst->fInst->clone(this);
            } else {
                return BasicCloneVisitor::visit(inst);
            }
        } else {
            return BasicCloneVisitor::visit(inst);
        }
    }

};

// FIR checker
struct FIRChecker : public DispatchVisitor {
    
    virtual void visit(BinopInst* inst)
    {
        Typed::VarType a1_type = TypingVisitor::getType(inst->fInst1);
        Typed::VarType a2_type = TypingVisitor::getType(inst->fInst2);
        if (a1_type == a2_type) {
            return;
        } else {
            bool v1 = isIntType(a1_type) && isBoolType(a2_type);
            bool v2 = isBoolType(a1_type) && isIntType(a2_type);
            if (v1 || v2) return;
        }
        // Fail
        dump2FIR(inst);
        std::cerr << "ASSERT : FIRChecker in BinopInst";
        std::cerr << " a1_type = " << Typed::gTypeString[a1_type];
        std::cerr << " a2_type = " << Typed::gTypeString[a2_type] << std::endl;
        faustassert(false);
    }
    
    virtual void visit(Select2Inst* inst)
    {
        Typed::VarType cond_type = TypingVisitor::getType(inst->fCond);
        if (!(isIntType(cond_type) || isBoolType(cond_type))) {
            dump2FIR(inst);
            std::cerr << "ASSERT : FIRChecker in Select2Inst";
            std::cerr << " cond_type = " << Typed::gTypeString[cond_type] << std::endl;
            faustassert(false);
        }
    }
    
    virtual void visit(::CastInst* inst)
    {
        Typed::VarType val_type = TypingVisitor::getType(inst->fInst);
        Typed::VarType cast_type = inst->fType->getType();

        if (isInt32Type(cast_type)) {
            if (isInt32Type(val_type)) {
                dump2FIR(inst);
                std::cerr << "ASSERT : FIRChecker in CastInst Int";
                std::cerr << " value_type = " << Typed::gTypeString[val_type];
                std::cerr << " cast_type = " << Typed::gTypeString[cast_type] << std::endl;
                faustassert(false);
            }
        } else if (isFloatType(cast_type)) {
            if (isFloatType(val_type)) {
                dump2FIR(inst);
                std::cerr << "ASSERT : FIRChecker in CastInst Float";
                std::cerr << " val_type = " << Typed::gTypeString[val_type];
                std::cerr << " cast_type = " << Typed::gTypeString[cast_type] << std::endl;
                faustassert(false);
            }
        } else if (isDoubleType(cast_type)) {
            if (isDoubleType(val_type)) {
                dump2FIR(inst);
                std::cerr << "ASSERT : FIRChecker in CastInst Double";
                std::cerr << " val_type = " << Typed::gTypeString[val_type];
                std::cerr << " cast_type = " << Typed::gTypeString[cast_type] << std::endl;
                faustassert(false);
            }
        }
    }
};

/*
  Remove usage of var address:
  int* v1 = &foo[n]; ==> v1 definition is removed, usage of v1[m] are replaced with foo[n+m]
  v1 = &foo[n];      ==> usage of v1[m] are replaced with foo[n+m]
 */
struct VarAddressRemover : public BasicCloneVisitor {
    
    std::map<std::string, LoadVarAddressInst*> fVariableMap;

    virtual StatementInst* visit(DeclareVarInst* inst)
    {
        LoadVarAddressInst* var_address = dynamic_cast<LoadVarAddressInst*>(inst->fValue);
        if (var_address) {
            fVariableMap[inst->fAddress->getName()] = var_address;
            return InstBuilder::genNullStatementInst();
        } else {
            return BasicCloneVisitor::visit(inst);
        }
    }

    virtual StatementInst* visit(StoreVarInst* inst)
    {
        LoadVarAddressInst* var_address = dynamic_cast<LoadVarAddressInst*>(inst->fValue);
        if (var_address) {
            fVariableMap[inst->fAddress->getName()] = var_address;
            return InstBuilder::genNullStatementInst();
        } else {
            return BasicCloneVisitor::visit(inst);
        }
    }

    virtual Address* visit(IndexedAddress* address)
    {
        if (fVariableMap.find(address->getName()) != fVariableMap.end()) {
            IndexedAddress* id_add1 = dynamic_cast<IndexedAddress*>(fVariableMap[address->getName()]->fAddress);
            IndexedAddress* id_add2 = dynamic_cast<IndexedAddress*>(address);
            faustassert(id_add2);
            faustassert(id_add1);
            ValueInst* id1 = id_add1->getIndex();
            ValueInst* id2 = id_add2->getIndex();
            return InstBuilder::genIndexedAddress(id_add1->fAddress->clone(this),
                                                  InstBuilder::genAdd(id1->clone(this), id2->clone(this)));
        } else {
            return BasicCloneVisitor::visit(address);
        }
    }

};

// Expand and rewrite ControlInst as 'IF (cond) {....}' instructions
struct ControlExpander : public BasicCloneVisitor {
    
    // To keep the current condition with the IfInst block which is progressively filled
    struct IfBlock {
        
        ValueInst* fCond;
        IfInst* fIfInst;
        
        IfBlock() { init(); }
        void init()
        {
            fCond = nullptr;
            fIfInst = nullptr;
        }
    };
    
    std::stack<BlockInst*> fBlockStack;
    std::stack<IfBlock> fIfBlockStack;
    
    void beginCond(ControlInst* inst);
    void continueCond(ControlInst* inst);
    void endCond();
    
    StatementInst* visit(ControlInst* inst);
    StatementInst* visit(BlockInst* inst);
    
};

// Base class for iConst/fConst memory copy in -osX modes
struct ConstantsCopyMemory : public BasicCloneVisitor {
    
    // Additional variables are added at the end of iZone/fZone arrays
    int fIntIndex = 0;
    int fRealIndex = 0;
    
    ConstantsCopyMemory(int int_index, int float_index):fIntIndex(int_index), fRealIndex(float_index)
    {}
    
    // Removed instructions
    StatementInst* visit(DeclareVarInst* inst)
    {
        return InstBuilder::genDropInst();
    }
    
    StatementInst* visit(ForLoopInst* inst)
    {
        return InstBuilder::genDropInst();
    }
    
};

// Analysis to copy constants from an external memory zone (FunArgs version) used in -os2 and -os3 modes
struct ConstantsCopyFromMemory : public ConstantsCopyMemory {
    
    ConstantsCopyFromMemory(int int_index, int float_index):ConstantsCopyMemory(int_index, float_index)
    {}
    
    StatementInst* visit(StoreVarInst* inst)
    {
        std::string name = inst->fAddress->getName();
        bool is_struct = inst->fAddress->getAccess() & Address::kStruct;
        if (startWith(name, "iConst") && is_struct) {
            ValueInst* zone = InstBuilder::genLoadArrayFunArgsVar("iZone", FIRIndex(fIntIndex++));
            return InstBuilder::genStoreVarInst(inst->fAddress->clone(this), zone);
        } else if (startWith(name, "fConst") && is_struct) {
            ValueInst* zone = InstBuilder::genLoadArrayFunArgsVar("fZone", FIRIndex(fRealIndex++));
            return InstBuilder::genStoreVarInst(inst->fAddress->clone(this), zone);
        } else if (name == "fSampleRate") {
            return BasicCloneVisitor::visit(inst);
        } else {
            return InstBuilder::genDropInst();
        }
    }
    
};

// Analysis to copy constants from an external memory zone (Struct version) used in -os2 and -os3 modes
struct ConstantsCopyFromMemory1 : public ConstantsCopyMemory {
    
    ConstantsCopyFromMemory1(int int_index, int float_index):ConstantsCopyMemory(int_index, float_index)
    {}
    
    StatementInst* visit(StoreVarInst* inst)
    {
        std::string name = inst->fAddress->getName();
        bool is_struct = inst->fAddress->getAccess() & Address::kStruct;
        if (startWith(name, "iConst") && is_struct) {
            ValueInst* zone = InstBuilder::genLoadArrayStructVar("iZone", FIRIndex(fIntIndex++));
            return InstBuilder::genStoreVarInst(inst->fAddress->clone(this), zone);
        } else if (startWith(name, "fConst") && is_struct) {
            ValueInst* zone = InstBuilder::genLoadArrayStructVar("fZone", FIRIndex(fRealIndex++));
            return InstBuilder::genStoreVarInst(inst->fAddress->clone(this), zone);
        } else if (name == "fSampleRate") {
            return BasicCloneVisitor::visit(inst);
        } else {
            return InstBuilder::genDropInst();
        }
    }
    
};

// Analysis to copy constants to an external memory zone (FunArgs version) used in -os2 and -os3 modes
struct ConstantsCopyToMemory : public ConstantsCopyMemory {
    
    ConstantsCopyToMemory(int int_index, int float_index):ConstantsCopyMemory(int_index, float_index)
    {}
    
    StatementInst* visit(StoreVarInst* inst)
    {
        std::string name = inst->fAddress->getName();
        bool is_struct = inst->fAddress->getAccess() & Address::kStruct;
        if (startWith(name, "iConst") && is_struct) {
            return InstBuilder::genStoreArrayFunArgsVar("iZone", FIRIndex(fIntIndex++), InstBuilder::genLoadStructVar(name));
        } else if (startWith(name, "fConst") && is_struct) {
            return InstBuilder::genStoreArrayFunArgsVar("fZone", FIRIndex(fRealIndex++), InstBuilder::genLoadStructVar(name));
        } else if (name == "fSampleRate") {
            return BasicCloneVisitor::visit(inst);
        } else {
            return InstBuilder::genDropInst();
        }
    }

};

// Analysis to copy constants to an external memory zone (Struct version) used in -os2 and -os3 modes
struct ConstantsCopyToMemory1 : public ConstantsCopyMemory {
    
    ConstantsCopyToMemory1(int int_index, int float_index):ConstantsCopyMemory(int_index, float_index)
    {}
    
    StatementInst* visit(StoreVarInst* inst)
    {
        std::string name = inst->fAddress->getName();
        bool is_struct = inst->fAddress->getAccess() & Address::kStruct;
        if (startWith(name, "iConst") && is_struct) {
            return InstBuilder::genStoreArrayStructVar("iZone", FIRIndex(fIntIndex++), InstBuilder::genLoadStructVar(name));
        } else if (startWith(name, "fConst") && is_struct) {
            return InstBuilder::genStoreArrayStructVar("fZone", FIRIndex(fRealIndex++), InstBuilder::genLoadStructVar(name));
        } else if (name == "fSampleRate") {
            return BasicCloneVisitor::visit(inst);
        } else {
            return InstBuilder::genDropInst();
        }
    }
    
};

// Rewrite DSP array fields as pointers
struct ArrayToPointer : public BasicCloneVisitor {
    
    virtual StatementInst* visit(DeclareVarInst* inst)
    {
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
        if (array_typed) {
            return InstBuilder::genDecStructVar(inst->getName(), InstBuilder::genArrayTyped(array_typed->fType->clone(this), 0));
        } else {
            return BasicCloneVisitor::visit(inst);
        }
    }
    
};

#endif
