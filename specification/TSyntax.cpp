#include "TSyntax.hh"

#include <map>

extern int gVecSize;
map<string, int> gIDCounters;

string getFreshID(const string& prefix)
{
	if (gIDCounters.find(prefix) == gIDCounters.end()) {
		gIDCounters[prefix] = 0;
	}
	int n = gIDCounters[prefix];
	gIDCounters[prefix] = n+1;
	return subst("$0$1", prefix, T(n));
}

// Indexes
TIndex* MR_VAR(const string& name) { return new TVarIndex(name); }
TIndex* MR_INT(int id) { return new TIntIndex(id); }

TIndex* MR_ADD(TIndex* v1, TIndex* v2) { return new TBinOpIndex(v1, v2, "+"); }
TIndex* MR_SUB(TIndex* v1, TIndex* v2) { return new TBinOpIndex(v1, v2, "-"); }
TIndex* MR_MUL(TIndex* v1, TIndex* v2) { return new TBinOpIndex(v1, v2, "*"); }
TIndex* MR_DIV(TIndex* v1, TIndex* v2) { return new TBinOpIndex(v1, v2, "/"); }
TIndex* MR_MOD(TIndex* v1, TIndex* v2) { return new TBinOpIndex(v1, v2, "%"); }

// Addresses
#ifdef ALT_VECTOR
TVectorAddress* MR_VECTOR_ADDRESS(const string& name, TType* type, int size) { return new TVectorAddress(name, type, size); }
#else
TNamedAddress* MR_VECTOR_ADDRESS(const string& name, TType* type) { return new TNamedAddress(name, type); }
#endif
TAddress* MR_INDEX_ADDRESS(TAddress* address, TIndex* id) { return new TIndexAddress(address, id); }
TAddress* MR_CAST_ADDRESS(TAddress* address, TType* type) { return new TCastAddress(address, type); }

// Types
vector<TVectorType*> gTypeTable;

TVectorType* MR_VECTOR_TYPE(TType* type, int size)
{
    vector<TVectorType*>::const_iterator it;
    for (it = gTypeTable.begin(); it != gTypeTable.end(); it++) {
        TVectorType* vec_type = (*it);
        if (vec_type->fType->equal(type) && vec_type->fSize == size) {
            return *it;
        }
    }
    TVectorType* new_type = new TVectorType(type, size, getFreshID("VecType"));
    gTypeTable.push_back(new_type);
    return new_type;
}
TIntType* MR_INT_TYPE() { return new TIntType(); };
TFloatType* MR_FLOAT_TYPE() { return new TFloatType(); };

// Statements
#ifdef ALT_VECTOR
TDeclareStatement* MR_DEC(TVectorAddress* vector) { return new TDeclareStatement(vector); }
#else
TDeclareStatement* MR_DEC(TNamedAddress* vector) { return new TDeclareStatement(vector); }
#endif

TDeclareTypeStatement* MR_DEC_TYPE(TType* type) { return new TDeclareTypeStatement(type); }
TBlockStatement* MR_BLOCK() { return new TBlockStatement(); }
TBlockStatement* MR_PUSH_BLOCK(TBlockStatement* block, TStatement* statement) { block->fCode.push_back(statement); return block; }
TStoreStatement* MR_STORE(TAddress* addr, TValue* val) { return new TStoreStatement(addr, val); }
TLoopStatement* MR_LOOP(int size, TIndex* index, TBlockStatement* code) { return new TLoopStatement(size, index, code); }
TSubLoopStatement* MR_SUBLOOP(int size, TIndex* index, TBlockStatement* code) { return new TSubLoopStatement(size, index, code); }
TIfStatement* MR_IF(TIndex* test, TBlockStatement* code) { return new TIfStatement(test, code); }

// Values
TNullValue* MR_NULL() { return new TNullValue(); }
TFloatValue* MR_FLOAT_VAL(float val) { return new TFloatValue(val); }
TIntValue* MR_INT_VAL(int val) { return new TIntValue(val); }
TLoadValue* MR_LOAD(TAddress* addr) { return new TLoadValue(addr); }

TPrimOpValue* MR_ADD(TValue* v1, TValue* v2) { return new TPrimOpValue(v1, v2, "+"); }
TPrimOpValue* MR_SUB(TValue* v1, TValue* v2) { return new TPrimOpValue(v1, v2, "-"); }
TPrimOpValue* MR_MUL(TValue* v1, TValue* v2) { return new TPrimOpValue(v1, v2, "*"); }
TPrimOpValue* MR_DIV(TValue* v1, TValue* v2) { return new TPrimOpValue(v1, v2, "/"); }
TPrimOpValue* MR_OP(TValue* v1, TValue* v2, const string& op)  { return new TPrimOpValue(v1, v2, op); }

void CHECK_EQUAL_TYPE(TType* type1, TType* type2)
{
    /*
    cout << "CHECK_EQUAL_TYPE" << endl;
    type1->generate(&cout, 0);
    cout << endl;
    type2->generate(&cout, 0);
    cout << endl;
    */
    assert(type1->equal(type2));
}

