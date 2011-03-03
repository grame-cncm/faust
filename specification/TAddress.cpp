
#include "TAddress.hh"
#include "TSyntax.hh"

#include <stack>

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

TAddress* TVectorAddress::rewriteAddress(list<TAddress*>& address_list)
{
    list<TAddress*>::iterator it1 = address_list.begin();
    TIndex* new_index = NULL;
    TAddress* new_address = this;
    stack<TCastAddress*> cast_stack;

    do {

        TCastAddress* cast_address = dynamic_cast<TCastAddress*>(*it1);
        TIndexAddress* index_address = dynamic_cast<TIndexAddress*>(*it1);

        if (cast_address) {
            new_index = MR_DIV(new_index, MR_INT(cast_address->fType->getSize()));
            cast_stack.push(cast_address);
        } else if (index_address) {
            it1++;
            if (it1 != address_list.end() && dynamic_cast<TCastAddress*>(*it1)) {
                new_index = index_address->fIndex;
            } else if (cast_stack.size() > 0) {
                new_index = MR_ADD(MR_MUL(new_index, MR_INT(cast_stack.top()->fType->getSize())), index_address->fIndex);
                cast_stack.pop();
                if (cast_stack.size() == 0)
                    new_address = MR_INDEX_ADDRESS(new_address, new_index);
            } else {
                new_address = MR_INDEX_ADDRESS(new_address, index_address->fIndex);
            }

            it1--;

        } else {
            assert(false);
        }

        it1++;

    } while (it1 != address_list.end());

    return new_address;
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

TAddress* TCastAddress::rewriteAddress(list<TAddress*>& address_list)
{
    address_list.push_front(this);
    return fAddress->rewriteAddress(address_list);
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

TAddress* TIndexAddress::rewriteAddress(list<TAddress*>& address_list)
{
    address_list.push_front(this);
    return fAddress->rewriteAddress(address_list);
}
