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
 
#include "instructions.hh"
#include "sigtype.hh"
#include "global.hh"
#include "floats.hh"

std::stack<BlockInst*> BasicCloneVisitor::fBlockStack;

string Typed::gTypeString[] = {
    "kInt32", "kInt32ish", "kInt32_ptr", "kInt32_vec", "kInt32_vec_ptr",
    "kInt64", "kInt64_ptr", "kInt64_vec", "kInt64_vec_ptr",
    "kBool", "kBool_ptr", "kBool_vec", "kBool_vec_ptr",
    "kFloat", "kFloatish", "kFloat_ptr", "kFloat_vec", "kFloat_vec_ptr",
    "kFloatMacro", "kFloatMacro_ptr",
    "kDouble", "kDoublish", "kDouble_ptr", "kDouble_vec", "kDouble_vec_ptr",
    "kQuad", "kQuad_ptr", "kQuad_vec", "kQuad_vec_ptr",
    "kVoid", "kVoid_ptr", "kVoid_ptr_ptr", "kObj", "kObj_ptr", "kNoType"
};

void BasicTyped::cleanup() { gGlobal->gTypeTable.clear(); }
void DeclareVarInst::cleanup() { gGlobal->gVarTypeTable.clear(); }

// Variable types are kept in the global name <===> type table
DeclareVarInst::DeclareVarInst(Address* address, Typed* type, ValueInst* value)
    :fAddress(address), fType(type), fValue(value)
{
    if (gGlobal->gVarTypeTable.find(fAddress->getName()) == gGlobal->gVarTypeTable.end()) {
        //cout << "DeclareVarInst " << fAddress->getName() << " " << Typed::gTypeString[type->getType()] << endl;
        gGlobal->gVarTypeTable[fAddress->getName()] = type;
    } else if (gGlobal->gVarTypeTable[fAddress->getName()] != type) {
        // If array type, check the internal type
        ArrayTyped* type1 = dynamic_cast<ArrayTyped*>(gGlobal->gVarTypeTable[fAddress->getName()]);
        ArrayTyped* type2 = dynamic_cast<ArrayTyped*>(type);
        if (type1 && type2) {
            faustassert(type1->fType == type2->fType);
        } else {
            faustassert(false);
        }
    }
}

DeclareVarInst::~DeclareVarInst()
{}

// Function types (return type) are kept in the global name <===> type table
DeclareFunInst::DeclareFunInst(const string& name, FunTyped* type, BlockInst* code)
        :fName(name), fType(type), fCode(code)
{
    if (gGlobal->gVarTypeTable.find(name) == gGlobal->gVarTypeTable.end()) {
        gGlobal->gVarTypeTable[name] = type->getTyped();
        //cout << "DeclareFunInst " << name << " " << Typed::gTypeString[type->getType()] << endl;
    } else if (gGlobal->gVarTypeTable[name] != type->getTyped()) {
        //cout << "DeclareFunInst " << name << endl;
        faustassert(false);
    }
}
 
DeclareFunInst::~DeclareFunInst()
{}
  
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

int BasicTyped::getSize() { return gGlobal->gTypeSizeMap[fType]; }

int FunTyped::getSize() { return gGlobal->gTypeSizeMap[Typed::kVoid_ptr]; }

int ArrayTyped::getSize() 
{ 
    if (fSize == 0) {
        // Array of zero size are treated as pointer in the corresponding type
        return gGlobal->gTypeSizeMap[getType()];
    } else {
        return fType->getSize() * fSize; 
    }
}

// Function argument variable types are kept in the global num <===> type table
NamedTyped* InstBuilder::genNamedTyped(const string& name, Typed* type)
{
    if (gGlobal->gVarTypeTable.find(name) == gGlobal->gVarTypeTable.end()) {
        //cout << "InstBuilder::genNamedTyped " << name << " " << Typed::gTypeString[type->getType()] << endl;
        gGlobal->gVarTypeTable[name] = type;
    }
    return new NamedTyped(name, type);
}

// Function argument variable types are kept in the global num <===> type table
NamedTyped* InstBuilder::genNamedTyped(const string& name, Typed::VarType type)
{
    return genNamedTyped(name, genBasicTyped(type));
}

ValueInst* InstBuilder::genCastNumFloatInst(ValueInst* inst)
{
    return InstBuilder::genCastInst(inst, InstBuilder::genBasicTyped(itfloat()));
}

ValueInst* InstBuilder::genCastNumFloatMacroInst(ValueInst* inst)
{
    return InstBuilder::genCastInst(inst, InstBuilder::genBasicTyped(Typed::kFloatMacro));
}

ValueInst* InstBuilder::genCastNumIntInst(ValueInst* inst)
{
    return InstBuilder::genCastInst(inst, InstBuilder::genBasicTyped(Typed::kInt32));
}

// BasicTyped are not cloned, but actually point on the same underlying type
Typed* BasicCloneVisitor::visit(BasicTyped* typed)
{
    return gGlobal->gTypeTable[typed->fType];
}

bool BlockInst::hasReturn()
{
    list<StatementInst*>::const_iterator it = fCode.end(); it--;
    return dynamic_cast<RetInst*>(*it);
}

// Return the block value (if is has one) and remove it from the block
ValueInst* BlockInst::getReturnValue()
{
    list<StatementInst*>::const_iterator it = fCode.end(); it--;
    RetInst* ret = dynamic_cast<RetInst*>(*it);
    if (ret) {
        fCode.pop_back();
        return ret->fResult;
    } else {
        return InstBuilder::genNullInst();
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
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid));
    return InstBuilder::genDeclareFunInst(name, fun_type, code);
}

DeclareFunInst* InstBuilder::genFunction0(const string& name, Typed::VarType res, BlockInst* code)
{
    list<NamedTyped*> args;
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    return InstBuilder::genDeclareFunInst(name, fun_type, code);
}

DeclareFunInst* InstBuilder::genFunction1(const string& name, Typed::VarType res, const string& arg1, Typed::VarType arg1_ty, BlockInst* code)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(arg1, arg1_ty));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    return InstBuilder::genDeclareFunInst(name, fun_type, code);
}

DeclareFunInst* InstBuilder::genFunction2(const string& name, Typed::VarType res,
                                          const string& arg1, Typed::VarType arg1_ty,
                                          const string& arg2, Typed::VarType arg2_ty, BlockInst* code)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(arg1, arg1_ty));
    args.push_back(InstBuilder::genNamedTyped(arg2, arg2_ty));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    return InstBuilder::genDeclareFunInst(name, fun_type, code);
}

DeclareFunInst* InstBuilder::genFunction3(const string& name, Typed::VarType res,
                                          const string& arg1, Typed::VarType arg1_ty,
                                          const string& arg2, Typed::VarType arg2_ty,
                                          const string& arg3, Typed::VarType arg3_ty, BlockInst* code)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(arg1, arg1_ty));
    args.push_back(InstBuilder::genNamedTyped(arg2, arg2_ty));
    args.push_back(InstBuilder::genNamedTyped(arg3, arg3_ty));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    return InstBuilder::genDeclareFunInst(name, fun_type, code);
}

DeclareFunInst* InstBuilder::genFunction4(const string& name, Typed::VarType res,
                                          const string& arg1, Typed::VarType arg1_ty,
                                          const string& arg2, Typed::VarType arg2_ty,
                                          const string& arg3, Typed::VarType arg3_ty,
                                          const string& arg4, Typed::VarType arg4_ty, BlockInst* code)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(arg1, arg1_ty));
    args.push_back(InstBuilder::genNamedTyped(arg2, arg2_ty));
    args.push_back(InstBuilder::genNamedTyped(arg3, arg3_ty));
    args.push_back(InstBuilder::genNamedTyped(arg4, arg4_ty));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    return InstBuilder::genDeclareFunInst(name, fun_type, code);
}

DeclareFunInst* InstBuilder::genFunction5(const string& name, Typed::VarType res,
                                          const string& arg1, Typed::VarType arg1_ty,
                                          const string& arg2, Typed::VarType arg2_ty,
                                          const string& arg3, Typed::VarType arg3_ty,
                                          const string& arg4, Typed::VarType arg4_ty,
                                          const string& arg5, Typed::VarType arg5_ty, BlockInst* code)
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

DeclareFunInst* InstBuilder::genFunction6(const string& name, Typed::VarType res,
                                          const string& arg1, Typed::VarType arg1_ty,
                                          const string& arg2, Typed::VarType arg2_ty,
                                          const string& arg3, Typed::VarType arg3_ty,
                                          const string& arg4, Typed::VarType arg4_ty,
                                          const string& arg5, Typed::VarType arg5_ty,
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
    printf("Dispatch2Visitor %d\n", inst->fSize);
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
bool  isTypeArray(Tree t, int* n, Tree& u)        { Tree x; return isTree(t, TYPEARRAY, x, u) && isInt(x->node(), n);     }

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
                dec_type = genDeclareTypeInst(InstBuilder::genBasicTyped(Typed::kInt32));
            } else if (type->nature() == kReal) {
                printf("FaustVectorType floatType \n");
                dec_type = genDeclareTypeInst(InstBuilder::genBasicTyped(Typed::kFloat));
            } else {
                faustassert(false);
            }
        } else if (FaustVectorType* vec = isVectorType(type)) {
            printf("FaustVectorType size %d\n", vec->size());
            DeclareTypeInst* sub_type = genType(vec->dereferenceType());
            dec_type = genDeclareTypeInst(genStructTyped(getFreshID("vecType"), InstBuilder::genArrayTyped(sub_type->fType, vec->size())));
        } else {
            faustassert(false);
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
        return InstBuilder::genBasicTyped(Typed::kInt32);
    } else if (isTypeFloat(t)) {
        printf("sharedTypeToFirType isTypeFloat\n");
        return InstBuilder::genBasicTyped(Typed::kFloat);
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
