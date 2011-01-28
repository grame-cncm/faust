#ifndef __TCompiler__
#define __TCompiler__

#include "TLang.hh"
#include "TSyntax.hh"

extern int gVecSize;
extern TBlockStatement* gExternalBlock;
extern TBlockStatement* gCurBlock;

struct TCompiler
{
    virtual ~TCompiler() {}

	virtual void compileTop(TSignal* signal)  // Here a single signal
    {
        compileVector(signal);
    }

    virtual void compileVector(TSignal* signal)
    {
        int rate = signal->getRate();
        TType* input_type = signal->getType();
        TType* output_type = MR_VECTOR_TYPE(MR_FLOAT_TYPE(), gVecSize);

        // assert output_type == input_type;

        TDeclareStatement* address = MR_ADDR("output", output_type);
        TIndex* in = MR_VAR("i");
        TListIndex* index_list = MR_INDEX_LIST();
        index_list = MR_PUSH_INDEX(index_list, in);

        // Compilation
        gCurBlock = MR_BLOCK();
        gExternalBlock = MR_BLOCK();
        signal->compileStatement(address, index_list, index_list);

        TLoopStatement* global_loop = MR_LOOP(rate * gVecSize, in, gCurBlock);

        // Code generation
        gExternalBlock->generate(&cout, 0);
        global_loop->generate(&cout, 0);
    }

};

#endif


