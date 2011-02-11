#ifndef __TCompiler__
#define __TCompiler__

#include "TLang.hh"
#include "TSyntax.hh"

extern int gVecSize;
extern TBlockStatement* gExternalBlock;

struct TCompiler
{
    virtual ~TCompiler() {}

	virtual void compileTop(TSignal* signal)  // Here a single signal
    {
        compileVector(signal);
    }

    virtual void compileVector(TSignal* signal)
    {
        int output_rate = signal->getRate();
        TType* input_type = signal->getType();
        TType* output_type = MR_VECTOR_TYPE(MR_FLOAT_TYPE(), output_rate * gVecSize);
        TVector* new_out_vec = MR_VECTOR("output", output_type);
        TIndex* var_in = MR_VAR("i");
        TAddress* out_address = MR_INDEX_ADDRESS(new_out_vec, var_in);

        input_type->generate(&cout, 0);
        out_address->generate(&cout, 0);

        // Compilation
        TBlockStatement* sub_block = MR_BLOCK();
        gExternalBlock = MR_BLOCK();
        signal->compileStatement(sub_block, out_address, var_in);
        TLoopStatement* global_loop = MR_LOOP(output_rate * gVecSize, var_in, sub_block);

        // Code generation
        cout << endl << "-----------------" << endl;
        cout << "Separated loops" << endl;
        cout << "-----------------" << endl;
        gExternalBlock->generate(&cout, 0);
        cout << endl << "-----------------" << endl;
        cout << "Result" << endl;
        cout << "-----------------" << endl;
        global_loop->generate(&cout, 0);
        cout << endl;
    }

};

#endif


