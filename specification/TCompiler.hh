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
        TVectorAddress* new_out_vec = MR_VECTOR_ADDRESS("output", MR_FLOAT_TYPE(), output_rate * gVecSize);
        TIndex* var_in = MR_VAR("i");
        TAddress* out_address = MR_INDEX_ADDRESS(new_out_vec, var_in);

        // Type checking
        new_out_vec->getType()->generate(&cout, 0);

        CHECK_TYPE(input_type, out_address->getType());

        assert(input_type->equal(out_address->getType()));

        // Compilation
        TBlockStatement* sub_block = MR_BLOCK();
        gExternalBlock = MR_BLOCK();
        gDecBlock = MR_BLOCK();
        signal->compileStatement(sub_block, out_address, var_in);
        TLoopStatement* global_loop = MR_LOOP(output_rate * gVecSize, var_in, sub_block);

        /*
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
        */

        // C++ code generation

       /* cout << "#include <stdio.h>" << endl;
        cout << "#include <string.h>" << endl << endl;

        cout << "// -----------------" << endl;
        cout << "// Declaration block" << endl;
        cout << "// -----------------" << endl;
        gDecBlock->generateCPP(&cout, 0);


        cout << endl << "void process()" << endl;
        cout << "{" << endl;

        cout << "\tfloat input0[32 * 16];" << endl;  // Should use real input rate....
        cout << "\tfloat input1[32 * 16];" << endl;
        cout << "\tfloat input2[32 * 16];" << endl;
        cout << "\tfloat input3[32 * 16];" << endl;
        cout << "\tfloat output[32 * 16];" << endl;

        // Should use real input rate....
        cout << "\tfor (int i = 0; i < 32 * 16; i++) {" << endl;
        cout << "\t\tinput0[i] = float(i);" << endl;
        cout << "\t\tinput1[i] = float(i);" << endl;
        cout << "\t\tinput2[i] = float(i);" << endl;
        cout << "\t\tinput3[i] = float(i);" << endl;
        cout << "\t}" << endl;

        cout << "\tmemset(output, 0, sizeof(float) * 32);" << endl;

        cout << endl << endl  << "\t// -----------------" << endl;
        cout << "\t// Separated loops" << endl;
        cout << "\t// -----------------" << endl;
        gExternalBlock->generateCPP(&cout, 1);

        cout << endl << "\t// -----------------" << endl;
        cout << "\t// Result" << endl;
        cout << "\t// -----------------" << endl;
        global_loop->generateCPP(&cout, 1);
        cout << endl;

        cout << "\tfor (int i = 0; i < 32; i++) {" << endl;
        cout << "\t\tprintf(\"output %f \\n\", output[i]);" << endl;
        cout << "\t}" << endl;

        cout << "}" << endl << endl;

        cout << "int main()" << endl;
         cout << "{" << endl;
        cout << "\tprocess();" << endl;
        cout << "}" << endl << endl;


      */

        // C++ code generation without aliasing

        cout << "#include <stdio.h>" << endl;
        cout << "#include <string.h>" << endl << endl;

        cout << "// -----------------" << endl;
        cout << "// Declaration block" << endl;
        cout << "// -----------------" << endl;
        gDecBlock->generateCPPNoAlias(&cout, 0);

        cout << endl << "void process()" << endl;
        cout << "{" << endl;

        cout << "\tfloat input0[32 * 16];" << endl;  // Should use real input rate....
        cout << "\tfloat input1[32 * 16];" << endl;
        cout << "\tfloat input2[32 * 16];" << endl;
        cout << "\tfloat input3[32 * 16];" << endl;
        cout << "\tfloat output[32 * 16];" << endl;

        // Should use real input rate....
        cout << "\tfor (int i = 0; i < 32 * 16; i++) {" << endl;
        cout << "\t\tinput0[i] = float(i);" << endl;
        cout << "\t\tinput1[i] = float(i);" << endl;
        cout << "\t\tinput2[i] = float(i);" << endl;
        cout << "\t\tinput3[i] = float(i);" << endl;
        cout << "\t}" << endl;

        cout << "\tmemset(output, 0, sizeof(float) * 32);" << endl;

        cout << endl << endl  << "\t// -----------------" << endl;
        cout << "\t// Separated loops" << endl;
        cout << "\t// -----------------" << endl;
        gExternalBlock->generateCPPNoAlias(&cout, 1);

        cout << endl << "\t// -----------------" << endl;
        cout << "\t// Result" << endl;
        cout << "\t// -----------------" << endl;
        global_loop->generateCPPNoAlias(&cout, 1);
        cout << endl;

        cout << "\tfor (int i = 0; i < 32; i++) {" << endl;
        cout << "\t\tprintf(\"output %f \\n\", output[i]);" << endl;
        cout << "\t}" << endl;

        cout << "}" << endl << endl;

        cout << "int main()" << endl;
        cout << "{" << endl;
        cout << "\tprocess();" << endl;
        cout << "}" << endl << endl;

    }

};

#endif


