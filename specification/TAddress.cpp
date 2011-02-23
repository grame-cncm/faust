
#include "TAddress.hh"
#include "TSyntax.hh"

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

