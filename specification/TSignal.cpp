#include "TSignal.hh"

#include "TSyntax.hh"

extern int gVecSize;

void TFloat::compileStatement(TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{
    gCurBlock->fCode.push_back(MR_STORE(address, Os, compileSample(Is)));
}

TValue* TFloat::compileSample(TListIndex* Is)
{
    return MR_FLOAT_VAL(fValue);
}

void TInt::compileStatement(TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{
    gCurBlock->fCode.push_back(MR_STORE(address, Os, compileSample(Is)));
}

TValue* TInt::compileSample(TListIndex* Is)
{
    return MR_INT_VAL(fValue);
}

void TInput::compileStatement(TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{
     gCurBlock->fCode.push_back(MR_STORE(address, Os, compileSample(Is)));
}

TValue* TInput::compileSample(TListIndex* Is)
{
    return MR_LOAD(MR_ADDR(subst("input$0", T(fIndex)), MR_VECTOR_TYPE(MR_FLOAT_TYPE(), gVecSize)), Is);
}

void TPrimOp::compileStatement(TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{
    gCurBlock->fCode.push_back(MR_STORE(address, Os, compileSample(Is)));
}

TValue* TPrimOp::compileSample(TListIndex* Is)
{
    // not shared
    //return MR_OP(fExp1->compileSample(Is), fExp2->compileSample(Is), fOp);

    // shared

    int rate = getRate();
    TType* type = getType();

    TIndex* var_j = MR_VAR("j");
    TListIndex* var_loop = MR_INDEX_LIST();
    var_loop = MR_PUSH_INDEX(var_loop, var_j);
    TDeclareStatement* new_out = MR_ADDR(getFreshID("TmpBinOp"), MR_VECTOR_TYPE(type, rate * gVecSize));

    // Internal block
    TBlockStatement* loop_code_block = MR_BLOCK();
    TStatement* res = MR_STORE(new_out, var_loop, MR_OP(fExp1->compileSample(var_loop), fExp2->compileSample(var_loop), fOp));
    MR_PUSH_BLOCK(loop_code_block, res);

    // Wrapping loop
    gExternalBlock->fCode.push_back(MR_LOOP(rate * gVecSize, var_j, loop_code_block));

    return MR_LOAD(new_out, Is);
}

void TVectorize::compileStatement(TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{
    // T = type(E)
    // T[n] = type(vectorize(E))

    // n * m = rate(E)
    // m = rate(vectorize(E))

    int rate = getRate();
    TType* type = getType();

    // shared
    //gCurBlock->fCode.push_back(MR_STORE(address, Os, compileSample(Is)));

    // not shared
    TIndex* var_k = MR_VAR("k");
    TListIndex* new_in_list = MR_ADD(MR_MUL(Is, MR_INT(fSize)), var_k);
    TListIndex* new_out_list = MR_PUSH_INDEX(Os, var_k);

    // Wrapping loop
    // Keep cur block
    TBlockStatement* old_block = gCurBlock;

    TBlockStatement* gCurBlock = MR_BLOCK();
    fExp->compileStatement(address, new_out_list, new_in_list);

    //old_block->fCode.push_back(new TSubLoopStatement(fSize, loop_id, gCurBlock));

    // Restore cur block
    //gCurBlock = old_block;

    // TO FINISH

    //gExternalBlock->fCode.push_back(new TSubLoopStatement(fSize, loop_id, cur_block));
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
    TDeclareStatement* new_out = MR_ADDR(getFreshID("TmpVectorize"), MR_VECTOR_TYPE(type, rate * gVecSize));

    // Compute new indexes
    TIndex* var_j = MR_VAR("j");
    TIndex* var_k = MR_VAR("k");

    TListIndex* new_in_list = MR_INDEX_LIST();
    new_in_list = MR_PUSH_INDEX(new_in_list, var_j);
    new_in_list = MR_PUSH_INDEX(new_in_list, var_k);

    TListIndex* new_out_list = MR_INDEX_LIST();
    new_out_list = MR_PUSH_INDEX(new_out_list, MR_ADD(MR_MUL(var_j, MR_INT(fSize)), var_k));

    // TO FINISH

    // Final value
    return MR_LOAD(new_out, Is);
}

void TSerialize::compileStatement(TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{
    int rate = getRate();
    TType* type = getType();

    // if not shared

    // if shared
    MR_STORE(address, Os, compileSample(Is));
}

TValue* TSerialize::compileSample(TListIndex* Is)
{
    int rate = getRate();
    int n = fExp->getRate();
    TType* type = getType();
    VectorType* vec_type = dynamic_cast<VectorType*>(type);
    assert(vec_type);

    // Declare output
    TDeclareStatement* new_out = MR_ADDR(getFreshID("TmpSerialize"), MR_VECTOR_TYPE(vec_type->fType, rate * gVecSize));

    // Compute new indexes
    TIndex* var_j = MR_VAR("j");
    TIndex* var_k = MR_VAR("k");

    TListIndex* new_in_list = MR_INDEX_LIST();
    new_in_list = MR_PUSH_INDEX(new_in_list, var_j);
    new_in_list = MR_PUSH_INDEX(new_in_list, var_k);

    TListIndex* new_out_list = MR_INDEX_LIST();
    new_out_list = MR_PUSH_INDEX(new_out_list, MR_ADD(MR_MUL(var_j, MR_INT(n)), var_k));

     // TO FINISH

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

void TConcat::compileStatement(TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{
    int rate = getRate();
    TType* type = getType();
    int size1 = fExp1->getType()->getSize();
    int size2 = fExp2->getType()->getSize();

    // if not shared
    /*
    fExp1->compileStatement(address, Os, Is);
    fExp2->compileStatement(address, MR_ADD(Os, MR_INT(size1)), Is);
    */

    // if shared
    gCurBlock->fCode.push_back(MR_STORE(address, Os, compileSample(Is)));
}

TValue* TConcat::compileSample(TListIndex* Is)
{
    int rate = getRate();
    TType* type = getType();
    int size1 = fExp1->getType()->getSize();
    int size2 = fExp2->getType()->getSize();

    // Declare output
    TDeclareStatement* new_out = MR_ADDR(getFreshID("TmpConcat"), MR_VECTOR_TYPE(type, rate * gVecSize));

    // Compute new indexes
    TIndex* var_j = MR_VAR("j");
    TIndex* var_k = MR_VAR("k");

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
    fExp1->compileStatement(new_out, new_out_list1, new_in_list);
    fExp2->compileStatement(new_out, new_out_list2, new_in_list);

    // Final value
    return MR_LOAD(new_out, Is);
}

void TDelayAt::compileStatement(TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{
    gCurBlock->fCode.push_back(MR_STORE(address, Os, compileSample(Is)));
}

TValue* TDelayAt::compileSample(TListIndex* Is)
{
    //return MR_LOAD(fExp1->compileSample(Is),
}

void TDelayLine::compileStatement(TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{

}

TValue* TDelayLine::compileSample(TListIndex* Is)
{

}

void TRecProj::compileStatement(TDeclareStatement* address, TListIndex* Os, TListIndex* Is)
{

}

TValue* TRecProj::compileSample(TListIndex* Is)
{

}


