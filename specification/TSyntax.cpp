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

TListIndex* MR_INDEX_LIST() { return new TListIndex(); }
TListIndex* MR_PUSH_INDEX(TListIndex* list, TIndex* index) { TListIndex* new_list = list->copy(); new_list->fIndexList.push_back(index); return new_list;}

TIndex* MR_ADD(TIndex* v1, TIndex* v2) { return new TBinOpIndex(v1, v2, "+"); }
TIndex* MR_SUB(TIndex* v1, TIndex* v2) { return new TBinOpIndex(v1, v2, "-"); }
TIndex* MR_MUL(TIndex* v1, TIndex* v2) { return new TBinOpIndex(v1, v2, "*"); }
TIndex* MR_DIV(TIndex* v1, TIndex* v2) { return new TBinOpIndex(v1, v2, "/"); }

TListIndex* MR_ADD(TListIndex* list, TIndex* v2) { TListIndex* new_list = list->copy(); assert(new_list->getStreamIndex()); new_list->setStreamIndex(new TBinOpIndex(new_list->getStreamIndex(), v2, "+")); return new_list; }
TListIndex* MR_SUB(TListIndex* list, TIndex* v2) { TListIndex* new_list = list->copy(); assert(new_list->getStreamIndex()); new_list->setStreamIndex(new TBinOpIndex(new_list->getStreamIndex(), v2, "_")); return new_list; }
TListIndex* MR_MUL(TListIndex* list, TIndex* v2) { TListIndex* new_list = list->copy(); assert(new_list->getStreamIndex()); new_list->setStreamIndex(new TBinOpIndex(new_list->getStreamIndex(), v2, "*")); return new_list; }
TListIndex* MR_DIV(TListIndex* list, TIndex* v2) { TListIndex* new_list = list->copy(); assert(new_list->getStreamIndex()); new_list->setStreamIndex(new TBinOpIndex(new_list->getStreamIndex(), v2, "/")); return new_list; }

// Types
TType* MR_VECTOR_TYPE(TType* type, int rate) { return new VectorType(type, rate); }
TType* MR_INT_TYPE() { return new TIntType(); };
TType* MR_FLOAT_TYPE() { return new TFloatType(); };

// Statements
TDeclareStatement* MR_ADDR(const string& name, TType* type) { return new TDeclareStatement(name, type); }
TBlockStatement* MR_BLOCK() { return new TBlockStatement(); }
TBlockStatement* MR_PUSH_BLOCK(TBlockStatement* block, TStatement* statement) { block->fCode.push_back(statement); return block; }
TStoreStatement* MR_STORE(TDeclareStatement* addr, TListIndex* list, TValue* val) { return new TStoreStatement(addr, list, val); }
TLoopStatement* MR_LOOP(int size, TIndex* index, TBlockStatement* code) { return new TLoopStatement(size, index, code); }
TSubLoopStatement* MR_SUBLOOP(int size, TIndex* index, TBlockStatement* code) { return new TSubLoopStatement(size, index, code); }
TIfStatement* MR_IF(TValue* test, TBlockStatement* code) { return new TIfStatement(test, code); }

// Values
TFloatValue* MR_FLOAT_VAL(float val) { return new TFloatValue(val); }
TIntValue* MR_INT_VAL(int val) { return new TIntValue(val); }
TLoadValue* MR_LOAD(TDeclareStatement* addr, TListIndex* index) { return new TLoadValue(addr, index); }

TPrimOpValue* MR_ADD(TValue* v1, TValue* v2) { return new TPrimOpValue(v1, v2, "+"); }
TPrimOpValue* MR_SUB(TValue* v1, TValue* v2) { return new TPrimOpValue(v1, v2, "_"); }
TPrimOpValue* MR_MUL(TValue* v1, TValue* v2) { return new TPrimOpValue(v1, v2, "*"); }
TPrimOpValue* MR_DIV(TValue* v1, TValue* v2) { return new TPrimOpValue(v1, v2, "/"); }
TPrimOpValue* MR_OP(TValue* v1, TValue* v2, const string& op)  { return new TPrimOpValue(v1, v2, op); }

