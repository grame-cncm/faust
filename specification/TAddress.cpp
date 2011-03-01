
#include "TAddress.hh"
#include "TSyntax.hh"

#ifdef ALT_VECTOR

void TVectorAddress::generate(ostream* dst, int n)
{
    fType->generate(dst, n);
    *dst << "[" << fSize << "]";
    *dst << " " << fName;
}

void TVectorAddress::generateCPP(ostream* dst, int n)
{
    *dst << fName;
}

void TVectorAddress::generateCPPNoAlias(ostream* dst, int n)
{
    *dst << fName;
}

TType* TVectorAddress::getType()
{
    return MR_VECTOR_TYPE(fType, fSize);
}

#else

void TVectorAddress::generate(ostream* dst, int n)
{
    fType->generate(dst, n);
    *dst << " " << fName;
}

void TVectorAddress::generateCPP(ostream* dst, int n)
{
    *dst << fName << ".f";
}

void TVectorAddress::generateCPPNoAlias(ostream* dst, int n)
{
    *dst << fName;
}

TType* TVectorAddress::getType()
{
    return fType;
}

#endif

TIndex* TVectorAddress::rewriteIndex(TIndex* index)
{
    //cout << "TVectorAddress::rewriteIndex " << fName << endl;
    return index;
}

TAddress* TVectorAddress::rewriteAddress(TIndex* index)
{
    return this;
}

void TCastAddress::generate(ostream* dst, int n)
{
    fAddress->generate(dst, n);
    *dst << "{"; fAddress->getType()->generate(dst, n); *dst << "->"; fType->generate(dst, n); *dst << "}";
}

void TCastAddress::generateCPP(ostream* dst, int n)
{
    *dst << "(*(";
    fType->generateCPP(dst, n);
    *dst << "*)&(";
    fAddress->generateCPP(dst, n);
    *dst << "))";
}

void TCastAddress::generateCPPNoAlias(ostream* dst, int n)
{
    *dst << "(*(";
    fType->generateCPPNoAlias(dst, n);
    *dst << "*)&(";
    fAddress->generateCPPNoAlias(dst, n);
    *dst << "))";
}

TType* TCastAddress::getType() { return fType; }

TIndex* TCastAddress::rewriteIndex(TIndex* index)
{
    return MR_DIV(fAddress->rewriteIndex(index), MR_INT(fType->getSize()));
}

TAddress* TCastAddress::rewriteAddress(TIndex* index)
{
    return fAddress->rewriteAddress(index);
}

void TIndexAddress::generate(ostream* dst, int n)
{
    fAddress->generate(dst, n);
    *dst << "("; fIndex->generate(dst, n); *dst << ")";
}

void TIndexAddress::generateCPP(ostream* dst, int n)
{
    fAddress->generateCPP(dst, n);
    if (dynamic_cast<TIndexAddress*>(fAddress) || dynamic_cast<TCastAddress*>(fAddress)) {
        *dst << ".f[";
    } else {
        *dst << "[";
    }
    fIndex->generateCPP(dst, n);
    *dst << "]";
}

void TIndexAddress::generateCPPNoAlias(ostream* dst, int n)
{
    fAddress->generateCPPNoAlias(dst, n);
    *dst << "[";
    fIndex->generateCPPNoAlias(dst, n);
    *dst << "]";
}

TType* TIndexAddress::getType()
{
    return fAddress->getType()->deref();
}

TIndex* TIndexAddress::rewriteIndex(TIndex* index)
{
    TVectorAddress* vec_address = dynamic_cast<TVectorAddress*>(fAddress);
    if (vec_address)
        return fIndex;
    else
        return MR_ADD(MR_MUL(fAddress->rewriteIndex(index), MR_INT(fAddress->getType()->getSize())), fIndex);

    //return MR_ADD(MR_MUL(fAddress->rewriteIndex(index), MR_INT(fAddress->getType()->getSize())), fIndex);
}

TAddress* TIndexAddress::rewriteAddress(TIndex* index)
{
    /*
    fIndex->generate(&cout, 0);
    cout << endl;
    TVectorAddress* vec_address = dynamic_cast<TVectorAddress*>(fAddress);
    if (vec_address)
        return new TIndexAddress(fAddress, index);
    else
        return fAddress->rewriteAddress(MR_ADD(MR_MUL(fAddress->rewriteIndex(index), MR_INT(fAddress->getType()->getSize())), fIndex));
    */

    /*
    TVectorAddress* vec_address = dynamic_cast<TVectorAddress*>(fAddress);

    if (vec_address)
        return new TIndexAddress(fAddress, index);
    else
        return new TIndexAddress(fAddress->rewriteAddress(index), fAddress->rewriteIndex(fIndex));
    */

    return MR_INDEX_ADDRESS(fAddress->rewriteAddress(index), fAddress->rewriteIndex(fIndex));
}
