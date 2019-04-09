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

#include "instructions.hh"
#include "floats.hh"
#include "global.hh"
#include "sigtype.hh"

// Used when inlining functions
std::stack<BlockInst*> BasicCloneVisitor::fBlockStack;

DeclareStructTypeInst* isStructType(const string& name)
{
    if (gGlobal->gVarTypeTable.find(name) != gGlobal->gVarTypeTable.end()) {
        Typed*         type     = gGlobal->gVarTypeTable[name];
        Typed::VarType ext_type = Typed::getTypeFromPtr(type->getType());
        // If type is an external Structured type
        if (gGlobal->gExternalStructTypes.find(ext_type) != gGlobal->gExternalStructTypes.end()) {
            return gGlobal->gExternalStructTypes[ext_type];
        }
    }
    return nullptr;
}

ValueInst* InstBuilder::genTypedZero(Typed::VarType type)
{
    if (type == Typed::kInt32) {
        return genInt32NumInst(0);
    } else if (type == Typed::kInt64) {
        return genInt64NumInst(0);
    } else if (isRealType(type)) {
        return genRealNumInst(type, 0.);
    } else {
        // Pointer type
        if (gGlobal->gMachinePtrSize == 4) {
            return genInt32NumInst(0);
        } else {
            return genInt64NumInst(0);
        }
    }
}

Typed::VarType ctType(Type t)
{
    return (t->nature() == kInt) ? Typed::kInt32 : Typed::kFloat;
}

string Typed::gTypeString[] = {"kInt32",          "kInt32_ptr",    "kInt32_vec",      "kInt32_vec_ptr",
                               "kInt64",          "kInt64_ptr",    "kInt64_vec",      "kInt64_vec_ptr",
                               "kBool",           "kBool_ptr",     "kBool_vec",       "kBool_vec_ptr",
                               "kFloat",          "kFloat_ptr",    "kFloat_ptr_ptr",  "kFloat_vec",
                               "kFloat_vec_ptr",  "kFloatMacro",   "kFloatMacro_ptr", "kFloatMacro_ptr_ptr",
                               "kDouble",         "kDouble_ptr",   "kDouble_ptr_ptr", "kDouble_vec",
                               "kDouble_vec_ptr", "kQuad",         "kQuad_ptr",       "kQuad_ptr_ptr",
                               "kQuad_vec",       "kQuad_vec_ptr", "kVoid",           "kVoid_ptr",
                               "kVoid_ptr_ptr",   "kObj",          "kObj_ptr",        "kSound",
                               "kSound_ptr",      "kUint_ptr",     "kNoType"};

void BasicTyped::cleanup()
{
    gGlobal->gTypeTable.clear();
}
void DeclareVarInst::cleanup()
{
    gGlobal->gVarTypeTable.clear();
}

// Variable types are kept in the global name <===> type table
DeclareVarInst::DeclareVarInst(Address* address, Typed* type, ValueInst* value)
    : fAddress(address), fType(type), fValue(value)
{
    if (gGlobal->gVarTypeTable.find(fAddress->getName()) == gGlobal->gVarTypeTable.end()) {
        gGlobal->gVarTypeTable[fAddress->getName()] = type;
    } else if (gGlobal->gVarTypeTable[fAddress->getName()] != type) {
        // If named type, check their name and internal type
        NamedTyped* name_t1 = dynamic_cast<NamedTyped*>(gGlobal->gVarTypeTable[fAddress->getName()]);
        NamedTyped* name_t2 = dynamic_cast<NamedTyped*>(type);
        if (name_t1 && name_t2) {
            faustassert(name_t1->fName == name_t2->fName && name_t1->fType == name_t2->fType);
        } else {
            // If array type, check their size and internal type
            ArrayTyped* array_t1 = dynamic_cast<ArrayTyped*>(gGlobal->gVarTypeTable[fAddress->getName()]);
            ArrayTyped* arry_t2  = dynamic_cast<ArrayTyped*>(type);
            if (array_t1 && arry_t2) {
                faustassert(array_t1->fSize == arry_t2->fSize && array_t1->fType == arry_t2->fType);
            } else {
                faustassert(false);
            }
        }
    }
}

// Function types (return type) are kept in the global name <===> type table
DeclareFunInst::DeclareFunInst(const string& name, FunTyped* type, BlockInst* code)
    : fName(name), fType(type), fCode(code)
{
    if (gGlobal->gVarTypeTable.find(name) == gGlobal->gVarTypeTable.end()) {
        gGlobal->gVarTypeTable[name] = type;
    } else {
        FunTyped* fun_type = static_cast<FunTyped*>(gGlobal->gVarTypeTable[name]);
        // If same result type
        if (fun_type->getTyped() == type->getTyped()) {
            if ((gGlobal->gOutputLang == "llvm") && (fun_type->getPrototype() != type->getPrototype())) {
                stringstream str;
                str << "ERROR : foreign function '" << name
                    << "' conflicts with another (possibly compiler internally defined) function with a different "
                       "prototype\n";
                throw faustexception(str.str());
            }
        } else {
            stringstream str;
            str << "ERROR : foreign function '" << name
                << "' conflicts with another (possibly compiler internally defined) function with a different return "
                   "type\n";
            throw faustexception(str.str());
        }
    }
}

BasicTyped* InstBuilder::genBasicTyped(Typed::VarType type)
{
    // Possibly force FAUSTFLOAT type (= kFloatMacro) to internal real
    Typed::VarType new_type = ((type == Typed::kFloatMacro) && gGlobal->gFAUSTFLOATToInternal) ? itfloat() : type;

    // If not defined, add the type in the table
    if (gGlobal->gTypeTable.find(new_type) == gGlobal->gTypeTable.end()) {
        gGlobal->gTypeTable[new_type] = new BasicTyped(new_type);
    }
    return gGlobal->gTypeTable[new_type];
}

int BasicTyped::getSize()
{
    faustassert(gGlobal->gTypeSizeMap.find(fType) != gGlobal->gTypeSizeMap.end());
    return gGlobal->gTypeSizeMap[fType];
}

int FunTyped::getSize()
{
    return gGlobal->gTypeSizeMap[Typed::kVoid_ptr];
}

int ArrayTyped::getSize()
{
    if (fSize == 0) {
        // Array of zero size are treated as pointer in the corresponding type
        faustassert(gGlobal->gTypeSizeMap.find(getType()) != gGlobal->gTypeSizeMap.end());
        return gGlobal->gTypeSizeMap[getType()];
    } else {
        return fType->getSize() * fSize;
    }
}

// Function argument variable types are kept in the global num <===> type table
NamedTyped* InstBuilder::genNamedTyped(const string& name, Typed* type)
{
    if (gGlobal->gVarTypeTable.find(name) == gGlobal->gVarTypeTable.end()) {
        // cout << "InstBuilder::genNamedTyped " << name << " " << Typed::gTypeString[type->getType()] << endl;
        gGlobal->gVarTypeTable[name] = type;
    }
    return new NamedTyped(name, type);
}

// Function argument variable types are kept in the global num <===> type table
NamedTyped* InstBuilder::genNamedTyped(const string& name, Typed::VarType type)
{
    return genNamedTyped(name, genBasicTyped(type));
}

ValueInst* InstBuilder::genCastFloatInst(ValueInst* inst)
{
    return InstBuilder::genCastInst(inst, InstBuilder::genBasicTyped(itfloat()));
}

ValueInst* InstBuilder::genCastFloatMacroInst(ValueInst* inst)
{
    return InstBuilder::genCastInst(inst, InstBuilder::genFloatMacroTyped());
}

ValueInst* InstBuilder::genCastInt32Inst(ValueInst* inst)
{
    return InstBuilder::genCastInst(inst, InstBuilder::genInt32Typed());
}

// BasicTyped are not cloned, but actually point on the same underlying type
Typed* BasicCloneVisitor::visit(BasicTyped* typed)
{
    return gGlobal->gTypeTable[typed->fType];
}

bool BlockInst::hasReturn()
{
    list<StatementInst*>::const_iterator it = fCode.end();
    it--;
    return dynamic_cast<RetInst*>(*it);
}

// Return the block value (if is has one) and remove it from the block
ValueInst* BlockInst::getReturnValue()
{
    list<StatementInst*>::const_iterator it = fCode.end();
    it--;
    RetInst* ret = dynamic_cast<RetInst*>(*it);
    if (ret) {
        fCode.pop_back();
        return ret->fResult;
    } else {
        return InstBuilder::genNullValueInst();
    }
}

struct StoreVarInst* DeclareVarInst::store(ValueInst* exp)
{
    return InstBuilder::genStoreVarInst(fAddress, exp);
}

struct LoadVarInst* DeclareVarInst::load()
{
    return InstBuilder::genLoadVarInst(fAddress);
}

// Function calls
DeclareFunInst* InstBuilder::genVoidFunction(const string& name, BlockInst* code)
{
    list<NamedTyped*> args;
    FunTyped*         fun_type = InstBuilder::genFunTyped(args, InstBuilder::genVoidTyped());
    return InstBuilder::genDeclareFunInst(name, fun_type, code);
}

DeclareFunInst* InstBuilder::genVoidFunction(const string& name, list<NamedTyped*>& args, BlockInst* code,
                                             bool isvirtual)
{
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genVoidTyped(),
                                                  (isvirtual) ? FunTyped::kVirtual : FunTyped::kDefault);
    return InstBuilder::genDeclareFunInst(name, fun_type, code);
}

DeclareFunInst* InstBuilder::genFunction0(const string& name, Typed::VarType res, BlockInst* code)
{
    list<NamedTyped*> args;
    FunTyped*         fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    return InstBuilder::genDeclareFunInst(name, fun_type, code);
}

DeclareFunInst* InstBuilder::genFunction1(const string& name, Typed::VarType res, const string& arg1,
                                          Typed::VarType arg1_ty, BlockInst* code)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(arg1, arg1_ty));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    return InstBuilder::genDeclareFunInst(name, fun_type, code);
}

DeclareFunInst* InstBuilder::genFunction2(const string& name, Typed::VarType res, const string& arg1,
                                          Typed::VarType arg1_ty, const string& arg2, Typed::VarType arg2_ty,
                                          BlockInst* code)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(arg1, arg1_ty));
    args.push_back(InstBuilder::genNamedTyped(arg2, arg2_ty));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    return InstBuilder::genDeclareFunInst(name, fun_type, code);
}

DeclareFunInst* InstBuilder::genFunction3(const string& name, Typed::VarType res, const string& arg1,
                                          Typed::VarType arg1_ty, const string& arg2, Typed::VarType arg2_ty,
                                          const string& arg3, Typed::VarType arg3_ty, BlockInst* code)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(arg1, arg1_ty));
    args.push_back(InstBuilder::genNamedTyped(arg2, arg2_ty));
    args.push_back(InstBuilder::genNamedTyped(arg3, arg3_ty));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    return InstBuilder::genDeclareFunInst(name, fun_type, code);
}

DeclareFunInst* InstBuilder::genFunction4(const string& name, Typed::VarType res, const string& arg1,
                                          Typed::VarType arg1_ty, const string& arg2, Typed::VarType arg2_ty,
                                          const string& arg3, Typed::VarType arg3_ty, const string& arg4,
                                          Typed::VarType arg4_ty, BlockInst* code)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(arg1, arg1_ty));
    args.push_back(InstBuilder::genNamedTyped(arg2, arg2_ty));
    args.push_back(InstBuilder::genNamedTyped(arg3, arg3_ty));
    args.push_back(InstBuilder::genNamedTyped(arg4, arg4_ty));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    return InstBuilder::genDeclareFunInst(name, fun_type, code);
}

DeclareFunInst* InstBuilder::genFunction5(const string& name, Typed::VarType res, const string& arg1,
                                          Typed::VarType arg1_ty, const string& arg2, Typed::VarType arg2_ty,
                                          const string& arg3, Typed::VarType arg3_ty, const string& arg4,
                                          Typed::VarType arg4_ty, const string& arg5, Typed::VarType arg5_ty,
                                          BlockInst* code)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(arg1, arg1_ty));
    args.push_back(InstBuilder::genNamedTyped(arg2, arg2_ty));
    args.push_back(InstBuilder::genNamedTyped(arg3, arg3_ty));
    args.push_back(InstBuilder::genNamedTyped(arg4, arg4_ty));
    args.push_back(InstBuilder::genNamedTyped(arg5, arg5_ty));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    return InstBuilder::genDeclareFunInst(name, fun_type, code);
}

DeclareFunInst* InstBuilder::genFunction6(const string& name, Typed::VarType res, const string& arg1,
                                          Typed::VarType arg1_ty, const string& arg2, Typed::VarType arg2_ty,
                                          const string& arg3, Typed::VarType arg3_ty, const string& arg4,
                                          Typed::VarType arg4_ty, const string& arg5, Typed::VarType arg5_ty,
                                          const string& arg6, Typed::VarType arg6_ty, BlockInst* code)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(arg1, arg1_ty));
    args.push_back(InstBuilder::genNamedTyped(arg2, arg2_ty));
    args.push_back(InstBuilder::genNamedTyped(arg3, arg3_ty));
    args.push_back(InstBuilder::genNamedTyped(arg4, arg4_ty));
    args.push_back(InstBuilder::genNamedTyped(arg5, arg5_ty));
    args.push_back(InstBuilder::genNamedTyped(arg6, arg6_ty));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    return InstBuilder::genDeclareFunInst(name, fun_type, code);
}

void ScalVecDispatcherVisitor::Dispatch2Visitor(ValueInst* inst)
{
    std::cout << "Dispatch2Visitor %d\n";
    fScalarVisitor->visit(inst);

    /*
     if (inst->fSize == 1) {
        fScalarVisitor->visit(inst);
     } else {
        fVectorVisitor->visit(inst);
     }
    */
}

//--------------------------
// Coding Types as trees
//--------------------------

// // 09/12/11 : HACK
/*
static Sym TYPEINT = symbol ("TypeInt");
Tree  typeInt()                    { return tree(TYPEINT);         }
bool  isTypeInt(Tree t)            { return isTree(t, TYPEINT);    }

static Sym TYPEFLOAT = symbol ("TypeFloat");
Tree  typeFloat()                { return tree(TYPEFLOAT);         }
bool  isTypeFloat(Tree t)        { return isTree(t, TYPEFLOAT);    }

static Sym TYPEARRAY = symbol ("TypeArray");
Tree  typeArray(int n, Tree t)                    { return tree(TYPEARRAY, tree(n), t);         }
bool  isTypeArray(Tree t, int* n, Tree& u)        { Tree x; return isTree(t, TYPEARRAY, x, u) && isInt(x->node(), n); }

static property<DeclareTypeInst* > gFirTypeProperty;

map<string, int> InstBuilder::fIDCounters;

static Tree signalTypeToSharedType(AudioType* type)
{
    if (isSimpleType(type)) {
        if (type->nature() == kInt32) {
            return typeInt();
        } else if (type->nature() == kReal) {
            return typeFloat();
        } else {
            faustassert(false);
        }
    } else if (FaustVectorType* vec = isVectorType(type)) {
        return typeArray(vec->size(), signalTypeToSharedType(vec->dereferenceType()));
    } else {
        faustassert(false);
    }
}

DeclareTypeInst* InstBuilder::genType(AudioType* type)
{
    Tree shared_type = signalTypeToSharedType(type);
    DeclareTypeInst* dec_type;

    if (gFirTypeProperty.get(shared_type, dec_type)) {
        return dec_type;
    } else {
        if (isSimpleType(type)) {
            if (type->nature() == kInt32) {
                printf("FaustVectorType intType \n");
                dec_type = genDeclareTypeInst(InstBuilder::genInt32Typed());
            } else if (type->nature() == kReal) {
                printf("FaustVectorType floatType \n");
                dec_type = genDeclareTypeInst(InstBuilder::genFloatTyped());
            } else {
                faustassert(false);
            }
        } else if (FaustVectorType* vec = isVectorType(type)) {
            printf("FaustVectorType size %d\n", vec->size());
            DeclareTypeInst* sub_type = genType(vec->dereferenceType());
            dec_type = genDeclareTypeInst(genStructTyped(getFreshID("vecType"),
InstBuilder::genArrayTyped(sub_type->fType, vec->size()))); } else { faustassert(false);
        }
    }

    gFirTypeProperty.set(shared_type, dec_type);
    return dec_type;
}

static Typed* sharedTypeToFirType(Tree t)
{
    int size;
    Tree subtree;

    if (isTypeInt(t)) {
        printf("sharedTypeToFirType isTypeInt\n");
        return InstBuilder::genInt32Typed();
    } else if (isTypeFloat(t)) {
        printf("sharedTypeToFirType isTypeFloat\n");
        return InstBuilder::genFloatTyped();
    } else if (isTypeArray(t, &size, subtree)) {
        printf("sharedTypeToFirType isTypeArray size %d\n", size);
        return InstBuilder::genArrayTyped(sharedTypeToFirType(subtree), size);
    } else {
        faustassert(false);
        return NULL;
    }
}

DeclareTypeInst* InstBuilder::genType(AudioType* type)
{
    Tree shared_type = signalTypeToSharedType(type);
    DeclareTypeInst* dec_type;

    if (gFirTypeProperty.get(shared_type, dec_type)) {
        return dec_type;
    } else {
        DeclareTypeInst* dec_type
            = genDeclareTypeInst(getFreshID("vecType"), sharedTypeToFirType(shared_type));
        gFirTypeProperty.set(shared_type, dec_type);
        return dec_type;
    }
}
*/
