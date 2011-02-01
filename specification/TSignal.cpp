#include "TSignal.hh"

#include "TSyntax.hh"

extern int gVecSize;

void TFloat::compileStatement(TBlockStatement* block, TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{
    block->fCode.push_back(MR_STORE(address, Os, compileSample(Is)));
}

TValue* TFloat::compileSample(TListIndex* Is)
{
    return MR_FLOAT_VAL(fValue);
}

void TInt::compileStatement(TBlockStatement* block, TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{
    block->fCode.push_back(MR_STORE(address, Os, compileSample(Is)));
}

TValue* TInt::compileSample(TListIndex* Is)
{
    return MR_INT_VAL(fValue);
}

void TInput::compileStatement(TBlockStatement* block, TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{
     block->fCode.push_back(MR_STORE(address, Os, compileSample(Is)));
}

TValue* TInput::compileSample(TListIndex* Is)
{
    return MR_LOAD(MR_ADDR(subst("input$0", T(fIndex)), MR_VECTOR_TYPE(MR_FLOAT_TYPE(), gVecSize)), Is);
}

void TPrimOp::compileStatement(TBlockStatement* block, TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{
    block->fCode.push_back(MR_STORE(address, Os, compileSample(Is)));
}

TValue* TPrimOp::compileSample(TListIndex* Is)
{
    // not shared
    //return MR_OP(fExp1->compileSample(Is), fExp2->compileSample(Is), fOp);

    // shared

    int rate = getRate();
    TType* type = getType();

    TIndex* var_j = MR_VAR(getFreshID("j"));
    TListIndex* var_loop = MR_INDEX_LIST();
    var_loop = MR_PUSH_INDEX(var_loop, var_j);
    TDeclareStatement* new_out = MR_ADDR(getFreshID("BinOp"), MR_VECTOR_TYPE(type, rate * gVecSize));

    // Internal block
    TBlockStatement* loop_code_block = MR_BLOCK();
    TStatement* res = MR_STORE(new_out, var_loop, MR_OP(fExp1->compileSample(var_loop), fExp2->compileSample(var_loop), fOp));
    MR_PUSH_BLOCK(loop_code_block, res);

    // Wrapping loop
    gExternalBlock->fCode.push_back(MR_LOOP(rate * gVecSize, var_j, loop_code_block));

    return MR_LOAD(new_out, Is);
}

void TVectorize::compileStatement(TBlockStatement* block, TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{
    // T = type(E)
    // T[n] = type(vectorize(E))

    // n * m = rate(E)
    // m = rate(vectorize(E))

    int rate = getRate();
    TType* type = getType();

    // not shared
    /*
    TIndex* var_k = MR_VAR(getFreshID("k"));
    TListIndex* new_in_list = MR_ADD(MR_MUL(Is, MR_INT(fSize)), var_k);
    TListIndex* new_out_list = MR_PUSH_INDEX(Os, var_k);

    // Wrapping loop
    TBlockStatement* sub_block = MR_BLOCK();
    fExp->compileStatement(sub_block, address, new_out_list, new_in_list);
    block->fCode.push_back(MR_SUBLOOP(fSize, var_k, sub_block));
    */

    // shared
    block->fCode.push_back(MR_STORE(address, Os, compileSample(Is)));
}

TValue* TVectorize::compileSample(TListIndex* Is)
{
    // T = type(E)
    // T[n] = type(vectorize(E))

    // n * m = rate(E)
    // m = rate(vectorize(E))

    int rate = getRate();
    TType* type = getType();

    // Declare output
    TDeclareStatement* new_out = MR_ADDR(getFreshID("Vectorize"), MR_VECTOR_TYPE(type, rate * gVecSize));

    // Compute new indexes
    TIndex* var_j = MR_VAR(getFreshID("j"));
    TIndex* var_k = MR_VAR(getFreshID("k"));

    TListIndex* new_in_list = MR_INDEX_LIST();
    new_in_list = MR_PUSH_INDEX(new_in_list, MR_ADD(MR_MUL(var_j, MR_INT(fSize)), var_k));

    TListIndex* new_out_list = MR_INDEX_LIST();
    new_out_list = MR_PUSH_INDEX(new_out_list, var_j);
    new_out_list = MR_PUSH_INDEX(new_out_list, var_k);

    // Wrapping loop
    TBlockStatement* sub_block = MR_BLOCK();
    fExp->compileStatement(sub_block, new_out, new_out_list, new_in_list);
    TSubLoopStatement* sub_loop = MR_SUBLOOP(fSize, var_k, sub_block);

    TBlockStatement* block = MR_BLOCK();
    block->fCode.push_back(sub_loop);
    gExternalBlock->fCode.push_back(MR_LOOP(rate * gVecSize, var_j, block));

    // Final value
    return MR_LOAD(new_out, Is);
}

void TSerialize::compileStatement(TBlockStatement* block, TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{
    int rate = getRate();
    int m = fExp->getRate();
    cerr << "TSerialize::compileStatement " << m << endl;
    assert(m > 0);
    int n = rate / m;
    TType* type = getType();

    // if not shared

    TBlockStatement* sub_block = MR_BLOCK();
    // TODO : add "if"

    TListIndex* new_in_list = MR_DIV(Is, MR_INT(n));
    fExp->compileStatement(sub_block, address, Os, new_in_list);  // Cast ??
    block->fCode.push_back(sub_block);

    // if shared
    ///block->fCode.push_back(MR_STORE(address, Os, compileSample(Is)));
}

TValue* TSerialize::compileSample(TListIndex* Is)
{
    int rate = getRate();
    int m = fExp->getRate();
    int n = rate / m;
    TType* type = getType();

    // Declare output
    TDeclareStatement* new_out = MR_ADDR(getFreshID("Serialize"), MR_VECTOR_TYPE(type, rate * gVecSize));

    // Compute new indexes
    TIndex* var_j = MR_VAR(getFreshID("j"));
    TIndex* var_k = MR_VAR(getFreshID("k"));

    TListIndex* new_in_list = MR_INDEX_LIST();
    new_in_list = MR_PUSH_INDEX(new_in_list, var_j);
    new_in_list = MR_PUSH_INDEX(new_in_list, var_k);

    TListIndex* new_out_list = MR_INDEX_LIST();
    new_out_list = MR_PUSH_INDEX(new_out_list, MR_ADD(MR_MUL(var_j, MR_INT(n)), var_k));

    // Wrapping loop
    TBlockStatement* sub_block = MR_BLOCK();
    fExp->compileStatement(sub_block, new_out, new_out_list, new_in_list);
    TSubLoopStatement* sub_loop = MR_SUBLOOP(n, var_k, sub_block);

    TBlockStatement* block = MR_BLOCK();
    block->fCode.push_back(sub_loop);
    gExternalBlock->fCode.push_back(MR_LOOP(m * gVecSize, var_j, block));

    // Final value
    return MR_LOAD(new_out, Is);
}

TType* TConcat::getType()
{
    TType* type1 = fExp1->getType();
    TType* type2 = fExp2->getType();
    VectorType* vec1_type = dynamic_cast<VectorType*>(type1);
    VectorType* vec2_type = dynamic_cast<VectorType*>(type2);
    assert(vec1_type && vec2_type && vec1_type->fType->equal(vec2_type->fType));
    return MR_VECTOR_TYPE(vec1_type->fType, vec1_type->fSize + vec2_type->fSize);
}

void TConcat::compileStatement(TBlockStatement* block, TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{
    int rate = getRate();
    TType* type = getType();
    int size1 = fExp1->getType()->getSize();
    int size2 = fExp2->getType()->getSize();

    // if not shared

    fExp1->compileStatement(block, address, Os, Is);
    fExp2->compileStatement(block, address, MR_ADD(Os, MR_INT(size1)), Is);


    // if shared
    //block->fCode.push_back(MR_STORE(address, Os, compileSample(Is)));
}

TValue* TConcat::compileSample(TListIndex* Is)
{
    int rate = getRate();
    TType* type = getType();
    int size1 = fExp1->getType()->getSize();
    int size2 = fExp2->getType()->getSize();

    // Declare output
    TDeclareStatement* new_out = MR_ADDR(getFreshID("Concat"), MR_VECTOR_TYPE(type, rate * gVecSize));
    // Compute new indexes
    TIndex* var_j = MR_VAR(getFreshID("j"));
    TIndex* var_k = MR_VAR(getFreshID("k"));

    /*
    TListIndex* new_in_list = MR_INDEX_LIST();
    new_in_list = MR_PUSH_INDEX(new_in_list, var_j);
    new_in_list = MR_PUSH_INDEX(new_in_list, var_k);

    TListIndex* new_out_list1 = MR_INDEX_LIST();
    new_out_list1 = MR_PUSH_INDEX(new_out_list1, var_j);
    new_out_list1 = MR_PUSH_INDEX(new_out_list1, var_k);

    TListIndex* new_out_list2 = MR_INDEX_LIST();
    new_out_list2 = MR_PUSH_INDEX(new_out_list2, var_j);
    new_out_list2 = MR_PUSH_INDEX(new_out_list2, MR_ADD(MR_INT(size1), var_k));

    // Compile sub-expressions
    TBlockStatement* sub_block1 = MR_BLOCK();
    fExp1->compileStatement(sub_block1, new_out, new_out_list1, new_in_list);
    TSubLoopStatement* sub_loop1 = MR_SUBLOOP(size1, var_k, sub_block1);

    TBlockStatement* sub_block2 = MR_BLOCK();
    fExp2->compileStatement(sub_block2, new_out, new_out_list2, new_in_list);
    TSubLoopStatement* sub_loop2 = MR_SUBLOOP(size2, var_k, sub_block2);

    TBlockStatement* block = MR_BLOCK();
    block->fCode.push_back(sub_loop1);
    block->fCode.push_back(sub_loop2);
    gExternalBlock->fCode.push_back(MR_LOOP(rate * gVecSize, var_j, block));
    */

    TListIndex* new_in_list = MR_INDEX_LIST();
    new_in_list = MR_PUSH_INDEX(new_in_list, var_j);

    TListIndex* new_out_list1 = MR_INDEX_LIST();
    new_out_list1 = MR_PUSH_INDEX(new_out_list1, var_j);
    new_out_list1 = MR_PUSH_INDEX(new_out_list1, MR_INT(0));

    TListIndex* new_out_list2 = MR_INDEX_LIST();
    new_out_list2 = MR_PUSH_INDEX(new_out_list2, var_j);
    new_out_list2 = MR_PUSH_INDEX(new_out_list2, MR_INT(size1));

    TBlockStatement* block = MR_BLOCK();
    fExp1->compileStatement(block, new_out, new_out_list1, new_in_list);
    fExp2->compileStatement(block, new_out, new_out_list2, new_in_list);

    gExternalBlock->fCode.push_back(MR_LOOP(rate * gVecSize, var_j, block));

    // Final value
    return MR_LOAD(new_out, Is);
}

void TVectorAt::compileStatement(TBlockStatement* block, TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{
    block->fCode.push_back(MR_STORE(address, Os, compileSample(Is)));
}

TValue* TVectorAt::compileSample(TListIndex* Is)
{
    TValue* res1 = fExp1->compileSample(Is);
    TValue* res2 = fExp2->compileSample(Is);

    TIntValue* id = dynamic_cast<TIntValue*>(res2);
    TLoadValue* val = dynamic_cast<TLoadValue*>(res1);

    assert(id && val);

    return MR_LOAD(val->fAddress, MR_PUSH_INDEX(val->fIndex, MR_INT(id->fValue)));
}

void TDelayLine::compileStatement(TBlockStatement* block, TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{

}

TValue* TDelayLine::compileSample(TListIndex* Is)
{

}

TDeclareStatement* TDelayLine::compile()
{
    int rate = getRate();
    TType* type = getType();

    // fMaxDelay is small

    // Declare output
    TDeclareStatement* new_out = MR_ADDR(getFreshID("DelayLine"), MR_VECTOR_TYPE(type, rate * gVecSize));

    // TODO : fill DL

    // Compute new indexes
    TIndex* var_j = MR_VAR(getFreshID("j"));

    TListIndex* new_in_list = MR_INDEX_LIST();
    new_in_list = MR_PUSH_INDEX(new_in_list, var_j);

    TListIndex* new_out_list = MR_INDEX_LIST();
    new_out_list = MR_PUSH_INDEX(new_out_list, MR_ADD(var_j, MR_INT(fMaxDelay)));

    TBlockStatement* block = MR_BLOCK();
    fExp->compileStatement(block, new_out, new_in_list, new_out_list);
    gExternalBlock->fCode.push_back(MR_LOOP(rate * gVecSize, var_j, block));

    return new_out;
}

void TDelayAt::compileStatement(TBlockStatement* block, TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{
    block->fCode.push_back(MR_STORE(address, Os, compileSample(Is)));
}

TValue* TDelayAt::compileSample(TListIndex* Is)
{
    TDelayLine* delay_line = dynamic_cast<TDelayLine*>(fExp1);
    assert(delay_line);

    TDeclareStatement* new_out = delay_line->compile();

    TValue* res2 = fExp2->compileSample(Is);
    TIntValue* id = dynamic_cast<TIntValue*>(res2);

    return MR_LOAD(new_out, MR_SUB(Is, MR_INT(id->fValue)));
}

void TRecProj::compileStatement(TBlockStatement* block, TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{
    block->fCode.push_back(MR_STORE(address, Os, compileSample(Is)));
}

TValue* TRecProj::compileSample(TListIndex* Is)
{
    TBlockStatement* block = MR_BLOCK();
    TDeclareStatement* res_out = NULL;

    int rate = getRate();

    // Compute new indexes
    TIndex* var_j = MR_VAR(getFreshID("j"));

    TListIndex* new_in_list = MR_INDEX_LIST();
    new_in_list = MR_PUSH_INDEX(new_in_list, var_j);

    TListIndex* new_out_list = MR_INDEX_LIST();
    new_out_list = MR_PUSH_INDEX(new_out_list, var_j);

    vector<TSignal*>::const_iterator it;
    int i = 0;
    for (it = fCode.begin(); it != fCode.end(); it++, i++) {

        TType* type = (*it)->getType();

        // Declare output
        TDeclareStatement* new_out = MR_ADDR(getFreshID("RecLine"), MR_VECTOR_TYPE(type, rate * gVecSize));
        if (i == fProj) res_out = new_out;

        (*it)->compileStatement(block, new_out, new_in_list, new_out_list);
    }

    gExternalBlock->fCode.push_back(MR_LOOP(rate * gVecSize, var_j, block));

    assert(res_out);
    return MR_LOAD(res_out, Is);
}


