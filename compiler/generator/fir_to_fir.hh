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

#ifndef _FIR_TO_FIR_H
#define _FIR_TO_FIR_H

#include "code_container.hh"
#include "fir_instructions.hh"
#include "instructions.hh"
#include "typing_instructions.hh"

// Tools to dump FIR
inline void dump2FIR(StatementInst* inst, std::ostream* out = &cerr)
{
    *out << "========== dump2FIR " << inst << " statement begin ========== " << std::endl;
    FIRInstVisitor fir_visitor(out);
    inst->accept(&fir_visitor);
    *out << "========== dump2FIR statement end ==========" << std::endl;
}

inline void dump2FIR(ValueInst* value, std::ostream* out = &cerr)
{
    *out << "========== dump2FIR " << value << " value begin ========== " << std::endl;
    FIRInstVisitor fir_visitor(out);
    value->accept(&fir_visitor);
    *out << "\n========== dump2FIR value end ==========" << std::endl;
}

inline void dump2FIR(Address* address, std::ostream* out = &cerr)
{
    *out << "========== dump2FIR " << address << " address begin ========== " << std::endl;
    FIRInstVisitor fir_visitor(out);
    address->accept(&fir_visitor);
    *out << "\n========== dump2FIR address end ==========" << std::endl;
}

inline void dump2FIR(Typed* type, std::ostream* out = &cerr)
{
    *out << "========== dump2FIR " << type << " type begin ========== " << std::endl;
    FIRInstVisitor fir_visitor(out);
    *out << fir_visitor.generateType(type);
    *out << "\n========== dump2FIR type end ==========" << std::endl;
}

bool sortArrayDeclarations(StatementInst* a, StatementInst* b);
bool sortTypeDeclarations(StatementInst* a, StatementInst* b);

// Analysis to change stack access to struct access
struct Stack2StructRewriter1 : public DispatchVisitor {
    string fName;

    using DispatchVisitor::visit;

    void visit(NamedAddress* address)
    {
        if (address->fAccess == Address::kStack && address->fName.find(fName) != string::npos) {
            address->fAccess = Address::kStruct;
        }
    }

    Stack2StructRewriter1(const string& name) : fName(name) {}
};

// Analysis to promote stack variables to struct variables
struct Stack2StructRewriter2 : public DispatchVisitor {
    CodeContainer* fContainer;
    string         fName;

    using DispatchVisitor::visit;

    void visit(DeclareVarInst* inst)
    {
        BasicCloneVisitor cloner;
        string            name = inst->fAddress->getName();

        if (inst->fAddress->getAccess() == Address::kStack && name.find(fName) != string::npos) {
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
        if (address->fAccess == Address::kStack && address->fName.find(fName) != string::npos) {
            address->fAccess = Address::kStruct;
        }
    }

    Stack2StructRewriter2(CodeContainer* container, const string& name) : fContainer(container), fName(name) {}
};

struct VariableMover {
    static void Move(CodeContainer* container, const string& name)
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

// Used in WebAssembly backends

/*
 For subcontainers table generation : rename 'sig' in 'dsp' and remove 'dsp' allocation
 (used in wast/wasm backends)
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

    BlockInst* getCode(BlockInst* src) { return static_cast<BlockInst*>(src->clone(this)); }
};

// Moves all variables declaration at the beginning of the block and rewrite them as 'declaration' followed by 'store'
struct MoveVariablesInFront2 : public BasicCloneVisitor {
    list<StatementInst*> fVarTable;

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
            list<StatementInst*> dec;
            list<StatementInst*> store;

            for (list<StatementInst*>::reverse_iterator it = fVarTable.rbegin(); it != fVarTable.rend(); ++it) {
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

            for (auto& it : store) {
                dst->pushFrontInst(it);
            }

            for (auto& it : dec) {
                dst->pushFrontInst(it);
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
        for (list<StatementInst*>::reverse_iterator it = fVarTableStore.rbegin(); it != fVarTableStore.rend(); ++it) {
            dst->pushFrontInst(*it);
        }
        // Then pure declaration
        for (list<StatementInst*>::reverse_iterator it = fVarTableDeclaration.rbegin();
             it != fVarTableDeclaration.rend(); ++it) {
            dst->pushFrontInst(*it);
        }
        return dst;
    }
};

// Inlining tools

struct FunctionInliner {
    map<string, string> fVarTable;

    BlockInst* ReplaceParameterByArg(BlockInst* code, NamedTyped* named, ValueInst* arg)
    {
        struct InlineValue : public BasicCloneVisitor {
            NamedTyped*          fNamed;
            ValueInst*           fArg;
            string               fInLoop;
            map<string, string>& fVarTable;
            int                  fOccurence;

            InlineValue(NamedTyped* named, ValueInst* arg, map<string, string>& table, int occurence)
                : fNamed(named), fArg(arg), fInLoop(""), fVarTable(table), fOccurence(occurence)
            {
            }

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
                    return InstBuilder::genDeclareVarInst(renameAddress(inst->fAddress, fInLoop),
                                                          inst->fType->clone(this),
                                                          (inst->fValue) ? inst->fValue->clone(this) : nullptr);
                } else {
                    return BasicCloneVisitor::visit(inst);
                }
            }

            ValueInst* visit(LoadVarInst* inst)
            {
                if (inst->fAddress->getAccess() == Address::kLoop) {
                    // Rename loop index
                    return InstBuilder::genLoadVarInst(renameAddress(inst->fAddress, fInLoop));
                } else {
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
            }

            StatementInst* visit(StoreVarInst* inst)
            {
                LoadVarInst* arg;

                if ((inst->fAddress->getName() == fNamed->fName) && (arg = dynamic_cast<LoadVarInst*>(fArg))) {
                    return InstBuilder::genStoreVarInst(renameAddress(inst->fAddress, arg->fAddress->getName()),
                                                        inst->fValue->clone(this));
                } else if (inst->fAddress->getAccess() == Address::kLoop) {
                    // Rename loop index
                    return InstBuilder::genStoreVarInst(renameAddress(inst->fAddress, fInLoop),
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

        InlineValue inliner(named, arg, fVarTable, counter.fOccurence);
        return inliner.getCode(code);
    }

    BlockInst* ReplaceParametersByArgs(BlockInst* code, list<NamedTyped*> args_type, list<ValueInst*> args,
                                       bool ismethod)
    {
        list<NamedTyped*>::iterator it1 = args_type.begin();
        list<ValueInst*>::iterator  it2 = args.begin();
        if (ismethod) {
            it2++;
        }

        for (; it1 != args_type.end(); it1++, it2++) {
            faustassert(it2 != args.end());
            code = ReplaceParameterByArg(code, *it1, *it2);
        }

        return code;
    }
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

    BlockInst* getCode(BlockInst* src) { return static_cast<BlockInst*>(src->clone(this)); }
};

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
            fSizeBytes += inst->fType->getSize();
        }
    }
};

// Remove unneeded cast
struct CastRemover : public BasicTypingCloneVisitor {
    virtual ValueInst* visit(::CastInst* inst)
    {
        inst->fInst->accept(&fTypingVisitor);
        Typed::VarType type = fTypingVisitor.fCurType;

        if (inst->fType->getType() == Typed::kInt32) {
            if (type == Typed::kInt32) {
                // std::cout << "CastInst : cast to int, but arg already int !" << std::endl;
                // dump2FIR(inst);
                return inst->fInst->clone(this);
            } else {
                /*
                // TODO = protection out-of [-2147483647, 2147483647] range
                ValueInst* max = InstBuilder::genRealNumInst(Typed::kFloat, double(2147483647));
                ValueInst* min = InstBuilder::genRealNumInst(Typed::kFloat, double(-2147483647));
                
                return InstBuilder::genSelect2Inst(InstBuilder::genGreaterEqual(inst->fInst->clone(this), max),
                                                   InstBuilder::genInt32NumInst(2147483647),
                                                   InstBuilder::genSelect2Inst(InstBuilder::genLessEqual(inst->fInst->clone(this), min),
                                                                               InstBuilder::genInt32NumInst(-2147483647),
                                                                               BasicTypingCloneVisitor::visit(inst)));
                */
                return BasicTypingCloneVisitor::visit(inst);
            }
        } else {
            if (isRealType(type)) {
                // std::cout << "CastInst : cast to real, but arg already real !" << std::endl;
                // dump2FIR(inst);
                return inst->fInst->clone(this);
            } else {
                return BasicTypingCloneVisitor::visit(inst);
            }
        }
    }

    BlockInst* getCode(BlockInst* src) { return static_cast<BlockInst*>(src->clone(this)); }
};

/*
  Remove usage of var address:
  int* v1 = &foo[n]; ==> v1 definition is removed, usage of v1[m] are replaced with foo[n+m]
  v1 = &foo[n];      ==> usage of v1[m] are replaced with foo[n+m]
 */
struct VarAddressRemover : public BasicCloneVisitor {
    std::map<string, LoadVarAddressInst*> fVariableMap;

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

    BlockInst* getCode(BlockInst* src) { return static_cast<BlockInst*>(src->clone(this)); }
};

/*
 Rename loop variable and all access (warning: does not work with nested loops with the same variable name...)
*/
struct LoopVariableRenamer : public BasicCloneVisitor {
    std::map<std::string, std::stack<std::string> > fLoopIndexMap;

    virtual StatementInst* visit(DeclareVarInst* inst)
    {
        // Rename 'loop' variables
        if (dynamic_cast<NamedAddress*>(inst->fAddress) && inst->fAddress->getAccess() == Address::kLoop) {
            std::string name = inst->fAddress->getName();
            fLoopIndexMap[name].push(gGlobal->getFreshID(name));
        }
        return BasicCloneVisitor::visit(inst);
    }

    virtual Address* visit(NamedAddress* address)
    {
        if (address->fAccess == Address::kLoop) {
            return new NamedAddress(fLoopIndexMap[address->getName()].top(), address->fAccess);
        } else {
            return BasicCloneVisitor::visit(address);
        }
    }

    BlockInst* getCode(BlockInst* src) { return static_cast<BlockInst*>(src->clone(this)); }
};

#endif
