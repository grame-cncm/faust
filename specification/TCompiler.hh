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
    #ifdef ALT_VECTOR
        TVectorAddress* new_out_vec = MR_VECTOR_ADDRESS("output", MR_FLOAT_TYPE(), output_rate * gVecSize);
    #else
        TVectorType* vec_type = MR_VECTOR_TYPE(MR_FLOAT_TYPE(), output_rate * gVecSize);
        TNamedAddress* new_out_vec = MR_VECTOR_ADDRESS("output", vec_type);
    #endif
        TIndex* var_in = MR_VAR("i");
        TAddress* out_address = MR_INDEX_ADDRESS(new_out_vec, var_in);

        // Type checking
        CHECK_EQUAL_TYPE(input_type, out_address->getType());

        // Compilation
        TBlockStatement* sub_block = MR_BLOCK();
        gExternalBlock = MR_BLOCK();
        gDecBlock = MR_BLOCK();

    #ifndef ALT_VECTOR
        MR_PUSH_BLOCK(gDecBlock, MR_DEC_TYPE(vec_type));
    #endif

        signal->compileStatement(sub_block, out_address, var_in);
        TLoopStatement* global_loop = MR_LOOP(output_rate * gVecSize, var_in, sub_block);

        // Pseudo code generation

        cout << "// -----------------" << endl;
        cout << "// Declaration block" << endl;
        cout << "// -----------------" << endl;
        gDecBlock->generate(&cout, 0);

        cout << endl << endl << "-----------------" << endl;
        cout << "Separated loops" << endl;
        cout << "-----------------" << endl;
        gExternalBlock->generate(&cout, 0);
        cout << endl << "-----------------" << endl;
        cout << "Result" << endl;
        cout << "-----------------" << endl;
        global_loop->generate(&cout, 0);
        cout << endl;

        // C++ code generation

/*
#ifdef ALT_VECTOR
        cout << "#include <stdio.h>" << endl;
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

        cout << "\tmemset(output, 0, sizeof(float) * 32 * 16);" << endl;

        cout << endl << endl << "\t// -----------------" << endl;
        cout << "\t// Separated loops" << endl;
        cout << "\t// -----------------" << endl;
        gExternalBlock->generateCPP(&cout, 1);

        cout << endl << "\t// -----------------" << endl;
        cout << "\t// Result" << endl;
        cout << "\t// -----------------" << endl;
        global_loop->generateCPP(&cout, 1);
        cout << endl;

        cout << "\tfor (int i = 0; i < 32 * 16; i++) {" << endl;
        cout << "\t\tprintf(\"output %f \\n\", output[i]);" << endl;
        cout << "\t}" << endl;

        cout << "}" << endl << endl;

        cout << "int main()" << endl;
        cout << "{" << endl;
        cout << "\tprocess();" << endl;
        cout << "}" << endl << endl;
  #else

        cout << "#include <stdio.h>" << endl;
        cout << "#include <string.h>" << endl << endl;

        cout << "// -----------------" << endl;
        cout << "// Declaration block" << endl;
        cout << "// -----------------" << endl;
        gDecBlock->generateCPP(&cout, 0);

        cout << endl << "void process()" << endl;
        cout << "{" << endl;

        cout << "\t" << vec_type->fDecName << " input0;" << endl;  // Should use real input rate....
        cout << "\t" << vec_type->fDecName << " input1;" << endl;
        cout << "\t" << vec_type->fDecName << " input2;" << endl;
        cout << "\t" << vec_type->fDecName << " input3;" << endl;
        cout << "\t" << vec_type->fDecName << " output;" << endl;

        // Should use real input rate....
        cout << "\tfor (int i = 0; i < sizeof(" << vec_type->fDecName << ") / sizeof(float); i++) {" << endl;
        cout << "\t\tinput0.f[i] = float(i);" << endl;
        cout << "\t\tinput1.f[i] = float(i);" << endl;
        cout << "\t\tinput2.f[i] = float(i);" << endl;
        cout << "\t\tinput3.f[i] = float(i);" << endl;
        cout << "\t\toutput.f[i] = 0.f;" << endl;
        cout << "\t}" << endl;

        cout << endl << endl  << "\t// -----------------" << endl;
        cout << "\t// Separated loops" << endl;
        cout << "\t// -----------------" << endl;
        gExternalBlock->generateCPP(&cout, 1);

        cout << endl << "\t// -----------------" << endl;
        cout << "\t// Result" << endl;
        cout << "\t// -----------------" << endl;
        global_loop->generateCPP(&cout, 1);
        cout << endl;

        cout << "\tfor (int i = 0; i < sizeof(" << vec_type->fDecName << ") / sizeof(float); i++) {" << endl;
        cout << "\t\tprintf(\"output %f \\n\", output.f[i]);" << endl;
        cout << "\t}" << endl;

        cout << "}" << endl << endl;

        cout << "int main()" << endl;
        cout << "{" << endl;
        cout << "\tprocess();" << endl;
        cout << "}" << endl << endl;
#endif
*/

        // C++ code generation without aliasing

#ifdef ALT_VECTOR
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

        cout << "\tmemset(output, 0, sizeof(float) * 32 * 16);" << endl;

        cout << endl << endl  << "\t// -----------------" << endl;
        cout << "\t// Separated loops" << endl;
        cout << "\t// -----------------" << endl;
        gExternalBlock->generateCPPNoAlias(&cout, 1);

        cout << endl << "\t// -----------------" << endl;
        cout << "\t// Result" << endl;
        cout << "\t// -----------------" << endl;
        global_loop->generateCPPNoAlias(&cout, 1);
        cout << endl;

        cout << "\tfor (int i = 0; i < 32 * 16; i++) {" << endl;
        cout << "\t\tprintf(\"output %f \\n\", output[i]);" << endl;
        cout << "\t}" << endl;

        cout << "}" << endl << endl;

        cout << "int main()" << endl;
        cout << "{" << endl;
        cout << "\tprocess();" << endl;
        cout << "}" << endl << endl;
  #else

        cout << "#include <stdio.h>" << endl;
        cout << "#include <string.h>" << endl << endl;

        cout << "// -----------------" << endl;
        cout << "// Declaration block" << endl;
        cout << "// -----------------" << endl;
        gDecBlock->generateCPPNoAlias(&cout, 0);

        cout << endl << "void process()" << endl;
        cout << "{" << endl;

        cout << "\t" << vec_type->fDecName << " input0;" << endl;  // Should use real input rate....
        cout << "\t" << vec_type->fDecName << " input1;" << endl;
        cout << "\t" << vec_type->fDecName << " input2;" << endl;
        cout << "\t" << vec_type->fDecName << " input3;" << endl;
        cout << "\t" << vec_type->fDecName << " output;" << endl;

        // Should use real input rate....
        cout << "\tfor (int i = 0; i < sizeof(" << vec_type->fDecName << ") / sizeof(float); i++) {" << endl;
        cout << "\t\tinput0[i] = float(i);" << endl;
        cout << "\t\tinput1[i] = float(i);" << endl;
        cout << "\t\tinput2[i] = float(i);" << endl;
        cout << "\t\tinput3[i] = float(i);" << endl;
        cout << "\t\toutput[i] = 0.f;" << endl;
        cout << "\t}" << endl;

        cout << endl << endl  << "\t// -----------------" << endl;
        cout << "\t// Separated loops" << endl;
        cout << "\t// -----------------" << endl;
        gExternalBlock->generateCPPNoAlias(&cout, 1);

        cout << endl << "\t// -----------------" << endl;
        cout << "\t// Result" << endl;
        cout << "\t// -----------------" << endl;
        global_loop->generateCPPNoAlias(&cout, 1);
        cout << endl;

        cout << "\tfor (int i = 0; i < sizeof(" << vec_type->fDecName << ") / sizeof(float); i++) {" << endl;
        cout << "\t\tprintf(\"output %f \\n\", output[i]);" << endl;
        cout << "\t}" << endl;

        cout << "}" << endl << endl;

        cout << "int main()" << endl;
        cout << "{" << endl;
        cout << "\tprocess();" << endl;
        cout << "}" << endl << endl;
#endif


    }

};

#endif


