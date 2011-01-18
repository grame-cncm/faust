/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2010 GRAME, Centre National de Creation Musicale
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

bool BlockInst::hasReturn()
{
    list<StatementInst*>::const_iterator it = fCode.end();
    it--;
    return dynamic_cast<RetInst*>(*it);
}

struct StoreVarInst * DeclareVarInst::store (ValueInst * exp)
{
    return InstBuilder::genStoreVarInst(fAddress, exp);
}

struct LoadVarInst * DeclareVarInst::load ()
{
    return InstBuilder::genLoadVarInst(fAddress);
}

DeclareFunInst* InstBuilder::genVoidFunction(const string& name)
{
    list<NamedTyped*> args;
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(Typed::kVoid));
    return InstBuilder::genDeclareFunInst(name, fun_type);
}

DeclareFunInst* InstBuilder::genFunction0(const string& name, Typed::VarType res)
{
    list<NamedTyped*> args;
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    return InstBuilder::genDeclareFunInst(name, fun_type);
}

DeclareFunInst* InstBuilder::genFunction1(const string& name, Typed::VarType res, const string& arg1, Typed::VarType arg1_ty)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(arg1, arg1_ty));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    return InstBuilder::genDeclareFunInst(name, fun_type);
}

DeclareFunInst* InstBuilder::genFunction2(const string& name, Typed::VarType res,
                                const string& arg1, Typed::VarType arg1_ty,
                                const string& arg2, Typed::VarType arg2_ty)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(arg1, arg1_ty));
    args.push_back(InstBuilder::genNamedTyped(arg2, arg2_ty));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    return InstBuilder::genDeclareFunInst(name, fun_type);
}

DeclareFunInst* InstBuilder::genFunction3(const string& name, Typed::VarType res,
                                const string& arg1, Typed::VarType arg1_ty,
                                const string& arg2, Typed::VarType arg2_ty,
                                const string& arg3, Typed::VarType arg3_ty)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(arg1, arg1_ty));
    args.push_back(InstBuilder::genNamedTyped(arg2, arg2_ty));
    args.push_back(InstBuilder::genNamedTyped(arg3, arg3_ty));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    return InstBuilder::genDeclareFunInst(name, fun_type);
}

DeclareFunInst* InstBuilder::genFunction4(const string& name, Typed::VarType res,
                                const string& arg1, Typed::VarType arg1_ty,
                                const string& arg2, Typed::VarType arg2_ty,
                                const string& arg3, Typed::VarType arg3_ty,
                                const string& arg4, Typed::VarType arg4_ty)
{
    list<NamedTyped*> args;
    args.push_back(InstBuilder::genNamedTyped(arg1, arg1_ty));
    args.push_back(InstBuilder::genNamedTyped(arg2, arg2_ty));
    args.push_back(InstBuilder::genNamedTyped(arg3, arg3_ty));
    args.push_back(InstBuilder::genNamedTyped(arg4, arg4_ty));
    FunTyped* fun_type = InstBuilder::genFunTyped(args, InstBuilder::genBasicTyped(res));
    return InstBuilder::genDeclareFunInst(name, fun_type);
}

//--------------------------
// Coding Types as trees
//--------------------------

Sym TYPEINT = symbol ("TypeInt");
Tree  typeInt()                    { return tree(TYPEINT);         }
bool  isTypeInt(Tree t)            { return isTree(t, TYPEINT);    }

Sym TYPEFLOAT = symbol ("TypeFloat");
Tree  typeFloat()                { return tree(TYPEFLOAT);         }
bool  isTypeFloat(Tree t)        { return isTree(t, TYPEFLOAT);    }

Sym TYPEARRAY = symbol ("TypeArray");
Tree  typeArray(int n, Tree t)                    { return tree(TYPEARRAY, tree(n), t);         }
bool  isTypeArray(Tree t, int* n, Tree& u)        { Tree x; return isTree(t, TYPEARRAY, x, u) && isInt(x->node(), n);     }

static property<DeclareTypeInst* > gFirTypeProperty;

map<string, int> InstBuilder::fIDCounters;

static Tree signalTypeToSharedType(AudioType* type)
{
    if (isSimpleType(type)) {
        if (type->nature() == kInt) {
            return typeInt();
        } else if (type->nature() == kReal) {
            return typeFloat();
        } else {
            assert(false);
        }
    } else if (FaustVectorType* vec = isVectorType(type)) {
        return typeArray(vec->size(), signalTypeToSharedType(vec->dereferenceType()));
    } else {
        assert(false);
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
            if (type->nature() == kInt) {
                printf("FaustVectorType intType \n");
                dec_type = genDeclareTypeInst(InstBuilder::genBasicTyped(Typed::kInt));
            } else if (type->nature() == kReal) {
                printf("FaustVectorType floatType \n");
                dec_type = genDeclareTypeInst(InstBuilder::genBasicTyped(Typed::kFloat));
            } else {
                assert(false);
            }
        } else if (FaustVectorType* vec = isVectorType(type)) {
            printf("FaustVectorType size %d\n", vec->size());
            DeclareTypeInst* sub_type = genType(vec->dereferenceType());
            dec_type = genDeclareTypeInst(genStructTyped(getFreshID("vecType"), InstBuilder::genArrayTyped(sub_type->fType, vec->size())));
        } else {
            assert(false);
        }
    }

    gFirTypeProperty.set(shared_type, dec_type);
    return dec_type;
}

/*
static Typed* sharedTypeToFirType(Tree t)
{
    int size;
    Tree subtree;

    if (isTypeInt(t)) {
        printf("sharedTypeToFirType isTypeInt\n");
        return InstBuilder::genBasicTyped(Typed::kInt);
    } else if (isTypeFloat(t)) {
        printf("sharedTypeToFirType isTypeFloat\n");
        return InstBuilder::genBasicTyped(Typed::kFloat);
    } else if (isTypeArray(t, &size, subtree)) {
        printf("sharedTypeToFirType isTypeArray size %d\n", size);
        return InstBuilder::genArrayTyped(sharedTypeToFirType(subtree), size);
    } else {
        assert(false);
        return NULL;
    }
}
*/

/*
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
