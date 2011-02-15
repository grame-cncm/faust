#ifndef __TCompiler__
#define __TCompiler__

#include "TLang.hh"
#include "TSyntax.hh"

extern int gVecSize;
extern TBlockStatement* gExternalBlock;
extern TBlockStatement* gDecBlock;

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
        TVector* new_out_vec = MR_VECTOR("output", MR_FLOAT_TYPE(), output_rate * gVecSize);
        TIndex* var_in = MR_VAR("i");
        TAddress* out_address = MR_INDEX_ADDRESS(new_out_vec, var_in);

        // Type checking
        CHECK_TYPE(input_type, out_address->getType());

        assert(input_type->equal(out_address->getType()));

        // Compilation
        TBlockStatement* sub_block = MR_BLOCK();
        gExternalBlock = MR_BLOCK();
        gDecBlock = MR_BLOCK();
        signal->compileStatement(sub_block, out_address, var_in);
        TLoopStatement* global_loop = MR_LOOP(output_rate * gVecSize, var_in, sub_block);


        // Pseudo code generation
        cout << endl << "-----------------" << endl;
        cout << "Separated loops" << endl;
        cout << "-----------------" << endl;
        gExternalBlock->generate(&cout, 0);
        cout << endl << "-----------------" << endl;
        cout << "Result" << endl;
        cout << "-----------------" << endl;
        global_loop->generate(&cout, 0);
        cout << endl;


        // C++ code generation
        cout << "#include <stdio.h>" << endl;
        cout << "#include <string.h>" << endl;

        cout << "void process() {" << endl;

        cout << "float input0[32];" << endl;
        cout << "float input1[32];" << endl;
        cout << "float input2[32];" << endl;
        cout << "float input3[32];" << endl;
        cout << "float output[32];" << endl;

        cout << "for (int i = 0; i < 32; i++) {" << endl;
        cout << "    input0[i] = float(i);" << endl;
        cout << "    input1[i] = float(i);" << endl;
        cout << "    input2[i] = float(i);" << endl;
        cout << "    input3[i] = float(i);" << endl;
        cout << "}" << endl;

        cout << " memset(output, 0, sizeof(float) * 32);" << endl;

        cout << endl << "// -----------------" << endl;
        cout << "// Declaration block" << endl;
        cout << "// -----------------" << endl;
        gDecBlock->generateCPP(&cout, 0);

        cout << endl << endl  << "// -----------------" << endl;
        cout << "// Separated loops" << endl;
        cout << "// -----------------" << endl;
        gExternalBlock->generateCPP(&cout, 0);

        cout << endl << "// -----------------" << endl;
        cout << "// Result" << endl;
        cout << "// -----------------" << endl;
        global_loop->generateCPP(&cout, 0);
        cout << endl;

        cout << "for (int i = 0; i < 32; i++) {" << endl;
        cout << "    printf(\"output %f \\n\", output[i]);" << endl;
        cout << "}" << endl;

        cout << "}" << endl;

        cout << "int main() {" << endl;
        cout << "    process();" << endl;
        cout << "}" << endl;

    }

};

#endif


