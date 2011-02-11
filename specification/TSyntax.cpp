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

// Address language
TVector* MR_VECTOR(const string& name, TType* type) { return new TVector(name, type); }
TAddress* MR_INDEX_ADDRESS(TAddress* address, TIndex* id) { return new TIndexAddress(address, id); }
TAddress* MR_CAST_ADDRESS(TAddress* address, TType* type) { return new TCastAddress(address, type); }

// Types
TType* MR_VECTOR_TYPE(TType* type, int size) { return new TVectorType(type, size); }
TType* MR_INT_TYPE() { return new TIntType(); };
TType* MR_FLOAT_TYPE() { return new TFloatType(); };

// Statements
TDeclareStatement* MR_DEC(TVector* vector) { return new TDeclareStatement(vector); }
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


void CHECK_TYPE(TType* type1, TType* type2)
{
    cout << "CHECK_TYPE" << endl;
    type1->generate(&cout, 0);
    cout << endl;
    type2->generate(&cout, 0);
    cout << endl;
    assert(type1->equal(type2));
}

