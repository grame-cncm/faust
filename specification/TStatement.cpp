
#include "TStatement.hh"
#include "TValue.hh"
#include "TSyntax.hh"

// Pseudo code generation
void TDeclareStatement::generate(ostream* dst, int n)
{
    tab(n, *dst);
    *dst << "Dec ";
    fVector->generate(dst, n);
}

void TDeclareTypeStatement::generate(ostream* dst, int n)
{
    tab(n, *dst);
    *dst << "DecType ";
    fType->generate(dst, n);
}

void TStoreStatement::generate(ostream* dst, int n)
{
    tab(n, *dst);
    fAddress->generate(dst, n);
    *dst << " = ";
    fValue->generate(dst, n);
}

void TBlockStatement::generate(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    for (it = fCode.begin(); it != fCode.end(); it++) {
        (*it)->generate(dst, n);
    }
}

void TLoopStatement::generate(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "for ("; fIndex->generate(dst, n); *dst << ", 0->"<< fSize << ", +1) {" << endl;
    fCode->generate(dst, n+1);
    tab(n, *dst); *dst << "}" << endl;
}

void TSubLoopStatement::generate(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "nestedfor ("; fIndex->generate(dst, n); *dst << ", 0->"<< fSize << ", +1) {" << endl;
    fCode->generate(dst, n+1);
    tab(n, *dst); *dst << "}";
}

void TIfStatement::generate(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "if ("; fIndex->generate(dst, n); *dst << " == 0) {" << endl;
    fCode->generate(dst, n+1);
    tab(n, *dst); *dst << "}";
}

// CPP generation
void TDeclareStatement::generateCPP(ostream* dst, int n)
{
    tab(n, *dst);
    fVector->fType->generateDef(dst, n);
    fVector->fType->generateCPP(dst, n);
    *dst << " ";
    *dst << fVector->fName;
#ifdef ALT_VECTOR
    *dst << "[" << fVector->fSize << "]";
#endif
    *dst << ";" << endl;
}

void TDeclareTypeStatement::generateCPP(ostream* dst, int n)
{
    fType->generateDef(dst, n);
}

void TStoreStatement::generateCPP(ostream* dst, int n)
{
    tab(n, *dst);
    fAddress->generateCPP(dst, n);
    *dst << " = ";
    fValue->generateCPP(dst, n);
    *dst << ";";
}

void TBlockStatement::generateCPP(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    for (it = fCode.begin(); it != fCode.end(); it++) {
        (*it)->generateCPP(dst, n);
    }
}

void TLoopStatement::generateCPP(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "for (int "; fIndex->generateCPP(dst, n);
        *dst << " = 0; ";
        fIndex->generateCPP(dst, n);
        *dst << " < " << fSize << "; ";
        fIndex->generateCPP(dst, n);
        *dst << "++) {" << endl;
    fCode->generateCPP(dst, n+1);
    tab(n, *dst); *dst << "}" << endl;
}

void TSubLoopStatement::generateCPP(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "for (int "; fIndex->generateCPP(dst, n);
        *dst << " = 0; ";
        fIndex->generateCPP(dst, n);
        *dst << " < " << fSize << "; ";
        fIndex->generateCPP(dst, n);
        *dst << "++) {" << endl;
    fCode->generateCPP(dst, n+1);
    tab(n, *dst); *dst << "}" << endl;
}

void TIfStatement::generateCPP(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "if ("; fIndex->generateCPP(dst, n); *dst << " == 0) {" << endl;
    fCode->generateCPP(dst, n+1);
    tab(n, *dst); *dst << "}";
}

// CPP generation no alias
void TDeclareStatement::generateCPPNoAlias(ostream* dst, int n)
{
    fVector->fType->generateDefNoAlias(dst, n);
    fVector->fType->generateCPPNoAlias(dst, n);
    *dst << " ";
    *dst << fVector->fName;
#ifdef ALT_VECTOR
    *dst << "[" << fVector->fSize << "]";
#endif
    *dst << ";" << endl;
}

void TDeclareTypeStatement::generateCPPNoAlias(ostream* dst, int n)
{
    fType->generateDefNoAlias(dst, n);
}

// Re-generate values with corrected addresses
TValue* TStoreStatement::generateSubValues(TValue* value, const vector<int>& dim)
{
    TLoadValue* load_value = dynamic_cast<TLoadValue*>(value);
    TPrimOpValue* prim_value = dynamic_cast<TPrimOpValue*>(value);

    if (load_value) {
        return MR_LOAD(generateSubAddressLoad(load_value->fAddress, dim));
    } else if (prim_value) {
        // Here we assume equals types...
        return MR_OP(generateSubValues(prim_value->fVal1, dim), generateSubValues(prim_value->fVal2, dim), prim_value->fOp);
    } else {
        return value;
    }
}

// Re-generate address with corrected indexing
TAddress* TStoreStatement::generateSubAddressStore(TAddress* address, const vector<int>& dim)
{
    TAddress* address1 = address;
    for (int i = 0; i < dim.size(); i++) {
        string index = subst("w$0", T(i));
        address1 = MR_INDEX_ADDRESS(address1, MR_VAR(index));
    }
    list<TAddress*> address_list;
    return address1->rewriteAddress(address_list);
}

TAddress* TStoreStatement::generateSubAddressLoad(TAddress* address, const vector<int>& dim)
{
    TAddress* address1 = address;
    for (int i = 0; i < dim.size(); i++) {
        string index = subst("w$0", T(i));
        address1 = MR_INDEX_ADDRESS(address1, MR_VAR(index));
    }
    return address1;
}

void TStoreStatement::generateSubLoops(ostream* dst, int n, const vector<int>& dim, int deep)
{
    if (deep == dim.size()) {
        tab(n, *dst);
        // Recompute address with corrected indexing
        generateSubAddressStore(fAddress, dim)->generateCPPNoAlias(dst, n);
        *dst << " = ";
        // Recompute address
        generateSubValues(fValue, dim)->generateCPPNoAlias(dst, n);
        *dst << ";" << endl;
    } else {
        tab(n, *dst);
        string index = subst("w$0", T(deep));
        *dst << "for (int " << index << " = 0; " << index << " < " << dim[deep] << "; " << index << "++) {" << endl;
        generateSubLoops(dst, n+1, dim, deep+1);
        tab(n, *dst);
        *dst << "}" << endl;
    }
}

void TStoreStatement::generateCPPNoAlias(ostream* dst, int n)
{
    CHECK_EQUAL_TYPE(fAddress->getType(), fValue->getType());

    // Operation on "simple" (= float) type
    if (dynamic_cast<TFloatType*>(fAddress->getType())) {
        tab(n, *dst);
        list<TAddress*> address_list;
        fAddress->rewriteAddress(address_list)->generateCPPNoAlias(dst, n);
        *dst << " = ";
        fValue->generateCPPNoAlias(dst, n);
        *dst << ";";
    } else {
        TVectorType* vec_type = dynamic_cast<TVectorType*>(fAddress->getType());
        assert(vec_type);
        generateSubLoops(dst, n, vec_type->dimensions(), 0);
    }
}

void TBlockStatement::generateCPPNoAlias(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    for (it = fCode.begin(); it != fCode.end(); it++) {
        (*it)->generateCPPNoAlias(dst, n);
    }
}

void TLoopStatement::generateCPPNoAlias(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "for (int "; fIndex->generateCPPNoAlias(dst, n);
        *dst << " = 0; ";
        fIndex->generateCPPNoAlias(dst, n);
        *dst << " < " << fSize << "; ";
        fIndex->generateCPPNoAlias(dst, n);
        *dst << "++) {" << endl;
    fCode->generateCPPNoAlias(dst, n+1);
    tab(n, *dst); *dst << "}" << endl;
}

void TSubLoopStatement::generateCPPNoAlias(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "for (int "; fIndex->generateCPPNoAlias(dst, n);
        *dst << " = 0; ";
        fIndex->generateCPPNoAlias(dst, n);
        *dst << " < " << fSize << "; ";
        fIndex->generateCPPNoAlias(dst, n);
        *dst << "++) {" << endl;
    fCode->generateCPPNoAlias(dst, n+1);
    tab(n, *dst); *dst << "}" << endl;
}

void TIfStatement::generateCPPNoAlias(ostream* dst, int n)
{
    vector<TStatement*>::const_iterator it;
    tab(n, *dst); *dst << "if ("; fIndex->generateCPPNoAlias(dst, n); *dst << " == 0) {" << endl;
    fCode->generateCPPNoAlias(dst, n+1);
    tab(n, *dst); *dst << "}";
}
