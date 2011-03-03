
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

TAddress* TVectorAddress::linearizeAddress(list<TAddress*>& address_list)
{
    list<TAddress*>::iterator it1 = address_list.begin();
    TVectorType* vec_type = dynamic_cast<TVectorType*>(fType);
    assert(vec_type);
    vector<int> dims;
    vector<TIndex*> indexes;

    TVectorType* new_vec_type = vec_type;

    vec_type->generate(&cout, 0);

    for (it1 = address_list.begin(); it1 != address_list.end(); it1++) {
        TCastAddress* cast_address = dynamic_cast<TCastAddress*>(*it1);
        TIndexAddress* index_address = dynamic_cast<TIndexAddress*>(*it1);
         if (cast_address) {
            int size = cast_address->fType->getSize();
            new_vec_type = MR_VECTOR_TYPE(MR_VECTOR_TYPE(new_vec_type->fType, size), new_vec_type->getSize()/size);
            new_vec_type->generate(&cout, 0);

         } else if (index_address) {
            indexes.push_back(index_address->fIndex);
         }
    }

    new_vec_type->generate(&cout, 0);

    /*

    for (it1 = address_list.begin(); it1 != address_list.end(); it1++) {
        TCastAddress* cast_address = dynamic_cast<TCastAddress*>(*it1);
        TIndexAddress* index_address = dynamic_cast<TIndexAddress*>(*it1);
         if (cast_address) {
             dims.push_back(cast_address->fType->getSize());
         } else if (index_address) {
            indexes.push_back(index_address->fIndex);
         }
    }
    */

    dims = new_vec_type->dimensions();
    TIndex* new_index = indexes[0];
    cout << "dims size "<< dims.size() << "indexes size " << indexes.size() << endl;
    for (int i = 0; i < dims.size()-1; i++) {
        new_index = MR_ADD(MR_MUL(new_index, MR_INT(dims[i+1])), indexes[i+1]);
    }

    return MR_INDEX_ADDRESS(this, new_index);
}

#else

void TNamedAddress::generate(ostream* dst, int n)
{
    fType->generate(dst, n);
    *dst << " " << fName;
}

void TNamedAddress::generateCPP(ostream* dst, int n)
{
    *dst << fName << ".f";
}

void TNamedAddress::generateCPPNoAlias(ostream* dst, int n)
{
    *dst << fName;
}

TType* TNamedAddress::getType()
{
    return fType;
}

TAddress* TNamedAddress::rewriteAddress(list<TAddress*>& address_list)
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

TAddress* TNamedAddress::linearizeAddress(list<TAddress*>& address_list)
{
    list<TAddress*>::iterator it1 = address_list.begin();
    TVectorType* vec_type = dynamic_cast<TVectorType*>(fType);
    assert(vec_type);
    vector<int> dims;
    vector<TIndex*> indexes;

    TVectorType* new_vec_type = vec_type;

    vec_type->generate(&cout, 0);

    for (it1 = address_list.begin(); it1 != address_list.end(); it1++) {
        TCastAddress* cast_address = dynamic_cast<TCastAddress*>(*it1);
        TIndexAddress* index_address = dynamic_cast<TIndexAddress*>(*it1);
         if (cast_address) {
            int size = cast_address->fType->getSize();
            new_vec_type = MR_VECTOR_TYPE(MR_VECTOR_TYPE(new_vec_type->fType, size), new_vec_type->getSize()/size);
            new_vec_type->generate(&cout, 0);

         } else if (index_address) {
            indexes.push_back(index_address->fIndex);
         }
    }

    new_vec_type->generate(&cout, 0);

    /*

    for (it1 = address_list.begin(); it1 != address_list.end(); it1++) {
        TCastAddress* cast_address = dynamic_cast<TCastAddress*>(*it1);
        TIndexAddress* index_address = dynamic_cast<TIndexAddress*>(*it1);
         if (cast_address) {
             dims.push_back(cast_address->fType->getSize());
         } else if (index_address) {
            indexes.push_back(index_address->fIndex);
         }
    }
    */

    dims = new_vec_type->dimensions();
    TIndex* new_index = indexes[0];
    cout << "dims size "<< dims.size() << "indexes size " << indexes.size() << endl;
    for (int i = 0; i < dims.size()-1; i++) {
        new_index = MR_ADD(MR_MUL(new_index, MR_INT(dims[i+1])), indexes[i+1]);
    }

    return MR_INDEX_ADDRESS(this, new_index);
}

#endif

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

TAddress* TCastAddress::linearizeAddress(list<TAddress*>& address_list)
{
    address_list.push_front(this);
    return fAddress->linearizeAddress(address_list);
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

TAddress* TIndexAddress::linearizeAddress(list<TAddress*>& address_list)
{
    address_list.push_front(this);
    return fAddress->linearizeAddress(address_list);
}
