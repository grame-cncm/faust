#include "TSignal.hh"
#include "TSyntax.hh"

#include <assert.h>

extern int gVecSize;

void TFloat::compileStatement(TBlockStatement* block, TAddress* address, TIndex* index)
{
    block->fCode.push_back(MR_STORE(address, compileSample(index)));
}

TValue* TFloat::compileSample(TIndex* index)
{
    return MR_FLOAT_VAL(fValue);
}

void TInt::compileStatement(TBlockStatement* block, TAddress* address, TIndex* index)
{
    block->fCode.push_back(MR_STORE(address, compileSample(index)));
}

TValue* TInt::compileSample(TIndex* index)
{
    return MR_INT_VAL(fValue);
}

void TInput::compileStatement(TBlockStatement* block, TAddress* address, TIndex* index)
{
     block->fCode.push_back(MR_STORE(address, compileSample(index)));
}

TValue* TInput::compileSample(TIndex* index)
{

#ifdef ALT_VECTOR
    return MR_LOAD(MR_INDEX_ADDRESS(MR_VECTOR_ADDRESS(subst("input$0", T(fIndex)), getType(), getRate() * gVecSize), index));
#else
    return MR_LOAD(MR_INDEX_ADDRESS(MR_VECTOR_ADDRESS(subst("input$0", T(fIndex)), MR_VECTOR_TYPE(getType(), getRate() * gVecSize)), index));
#endif
}

void TPrimOp::compileStatement(TBlockStatement* block, TAddress* address, TIndex* index)
{
    block->fCode.push_back(MR_STORE(address, compileSample(index)));
}

TValue* TPrimOp::compileSample(TIndex* index)
{
    // Expression type checking
    //CHECK_EQUAL_TYPE(fExp1->getType(), fExp2->getType());

    // not shared
    if (!gPrim) {
        return MR_OP(fExp1->compileSample(index), fExp2->compileSample(index), fOp);
    } else {
        // shared
        int rate = getRate();
        TType* type = getType();

        TIndex* var_j = MR_VAR(getFreshID("j"));

    #ifdef ALT_VECTOR
        TVectorAddress* new_out_vec = MR_VECTOR_ADDRESS(getFreshID("BinOp"), type, rate * gVecSize);
    #else
        TType* vec_type = MR_VECTOR_TYPE(type, rate * gVecSize);
        MR_PUSH_BLOCK(gDecBlock, MR_DEC_TYPE(vec_type));
        TNamedAddress* new_out_vec = MR_VECTOR_ADDRESS(getFreshID("BinOp"), vec_type);
    #endif

        // Internal block
        TBlockStatement* loop_code_block = MR_BLOCK();
        MR_PUSH_BLOCK(gDecBlock, MR_DEC(new_out_vec));
        TStatement* res = MR_STORE(MR_INDEX_ADDRESS(new_out_vec, var_j), MR_OP(fExp1->compileSample(var_j), fExp2->compileSample(var_j), fOp));
        MR_PUSH_BLOCK(loop_code_block, res);

        // Wrapping loop
        gExternalBlock->fCode.push_back(MR_LOOP(rate * gVecSize, var_j, loop_code_block));

        return MR_LOAD(MR_INDEX_ADDRESS(new_out_vec, index));
    }
}

void TVectorize::compileStatement(TBlockStatement* block, TAddress* address, TIndex* index)
{
    // T = type(E)
    // T[n] = type(vectorize(E))

    // n * m = rate(E)
    // m = rate(vectorize(E))

    int rate = getRate();
    TType* type = getType();

    // Address type checking
    CHECK_EQUAL_TYPE(address->getType(), type);

    // not shared
    if (!gVec) {
        TIndex* var_k = MR_VAR(getFreshID("k"));
        TIndex* new_in = MR_ADD(MR_MUL(index, MR_INT(fSize)), var_k);

        // Wrapping loop
        TBlockStatement* sub_block = MR_BLOCK();
        fExp->compileStatement(sub_block, MR_INDEX_ADDRESS(address, var_k), new_in);
        block->fCode.push_back(MR_SUBLOOP(fSize, var_k, sub_block));
    } else {
        // shared
        block->fCode.push_back(MR_STORE(address, compileSample(index)));
    }
}

TType* TVectorize::getType() { return MR_VECTOR_TYPE(fExp->getType(), fSize); }

TValue* TVectorize::compileSample(TIndex* index)
{
    // T = type(E)
    // T[n] = type(vectorize(E))

    // n * m = rate(E)
    // m = rate(vectorize(E))

    int rate = getRate();
    TType* type = getType();

    // Declare output
#ifdef ALT_VECTOR
    TVectorAddress* new_out_vec = MR_VECTOR_ADDRESS(getFreshID("Vectorize"), type, rate * gVecSize);
#else
    TType* vec_type = MR_VECTOR_TYPE(type, rate * gVecSize);
    MR_PUSH_BLOCK(gDecBlock, MR_DEC_TYPE(vec_type));
    TNamedAddress* new_out_vec = MR_VECTOR_ADDRESS(getFreshID("Vectorize"), vec_type);
#endif

    // Compute new indexes
    TIndex* var_j = MR_VAR(getFreshID("j"));
    TIndex* var_k = MR_VAR(getFreshID("k"));

    TIndex* new_in = MR_ADD(MR_MUL(var_j, MR_INT(fSize)), var_k);

    // Wrapping loop
    TBlockStatement* sub_block = MR_BLOCK();
    MR_PUSH_BLOCK(gDecBlock, MR_DEC(new_out_vec));
    fExp->compileStatement(sub_block, MR_INDEX_ADDRESS(MR_INDEX_ADDRESS(new_out_vec, var_j), var_k), new_in);
    TSubLoopStatement* sub_loop = MR_SUBLOOP(fSize, var_k, sub_block);

    TBlockStatement* block = MR_BLOCK();
    block->fCode.push_back(sub_loop);
    gExternalBlock->fCode.push_back(MR_LOOP(rate * gVecSize, var_j, block));

    // Output type checking
    CHECK_EQUAL_TYPE(type, MR_INDEX_ADDRESS(new_out_vec, index)->getType());

    // Final value
    return MR_LOAD(MR_INDEX_ADDRESS(new_out_vec, index));
}

void TSerialize::compileStatement(TBlockStatement* block, TAddress* address, TIndex* index)
{
    int rate = getRate();
    int m = fExp->getRate();
    assert(m > 0);
    int n = rate / m;
    TType* type = getType();

    // Address type checking
    CHECK_EQUAL_TYPE(address->getType(), type);

    // if not shared

    if (!gSer) {
        TBlockStatement* sub_block = MR_BLOCK();
        TIndex* new_in = MR_DIV(index, MR_INT(n));
        MR_PUSH_BLOCK(gDecBlock, MR_DEC_TYPE(MR_VECTOR_TYPE(type, n)));
        fExp->compileStatement(sub_block,
                            MR_CAST_ADDRESS(address, MR_VECTOR_TYPE(type, n)),
                            new_in);
        block->fCode.push_back(MR_IF(MR_MOD(index, MR_INT(n)), sub_block));
    } else {
        block->fCode.push_back(MR_STORE(address, compileSample(index)));
    }
}

TValue* TSerialize::compileSample(TIndex* index)
{
    int rate = getRate();
    int m = fExp->getRate();
    int n = rate / m;
    TType* type = getType();

    // Declare output
#ifdef ALT_VECTOR
    TVectorAddress* new_out_vec = MR_VECTOR_ADDRESS(getFreshID("Serialize"), type, rate * gVecSize);
#else
    TType* vec_type = MR_VECTOR_TYPE(type, rate * gVecSize);
    MR_PUSH_BLOCK(gDecBlock, MR_DEC_TYPE(vec_type));
    TNamedAddress* new_out_vec = MR_VECTOR_ADDRESS(getFreshID("Serialize"), vec_type);
#endif

    // Compute new indexes
    TIndex* var_j = MR_VAR(getFreshID("j"));

    TBlockStatement* sub_block = MR_BLOCK();
    TIndex* new_in = MR_DIV(var_j, MR_INT(n));

    MR_PUSH_BLOCK(gDecBlock, MR_DEC(new_out_vec));
    MR_PUSH_BLOCK(gDecBlock, MR_DEC_TYPE(MR_VECTOR_TYPE(type, n)));
    fExp->compileStatement(sub_block,
                        MR_CAST_ADDRESS(MR_INDEX_ADDRESS(new_out_vec, var_j), MR_VECTOR_TYPE(type, n)),
                        new_in);

    TBlockStatement* sub_block2 = MR_BLOCK();
    sub_block2->fCode.push_back(MR_IF(MR_MOD(var_j, MR_INT(n)), sub_block));

    gExternalBlock->fCode.push_back(MR_LOOP(n * m * gVecSize, var_j, sub_block2));

    // Output type checking
    CHECK_EQUAL_TYPE(type, MR_INDEX_ADDRESS(new_out_vec, index)->getType());

    // Final value
    return MR_LOAD(MR_INDEX_ADDRESS(new_out_vec, index));
}

TType* TConcat::getType()
{
    TType* type1 = fExp1->getType();
    TType* type2 = fExp2->getType();
    TVectorType* vec1_type = dynamic_cast<TVectorType*>(type1);
    TVectorType* vec2_type = dynamic_cast<TVectorType*>(type2);
    assert(vec1_type && vec2_type && vec1_type->fType->equal(vec2_type->fType));
    return MR_VECTOR_TYPE(vec1_type->fType, vec1_type->fSize + vec2_type->fSize);
}

void TConcat::compileStatement(TBlockStatement* block, TAddress* address, TIndex* index)
{
    int rate = getRate();
    TType* type = getType();
    TType* type1 = fExp1->getType();
    TType* type2 = fExp2->getType();
    int size1 = type1->getSize();
    int size2 = type2->getSize();

    // Address type checking
    CHECK_EQUAL_TYPE(address->getType(), type);

    // if not shared
    if (!gConcat) {
        MR_PUSH_BLOCK(gDecBlock, MR_DEC_TYPE(type1));
        MR_PUSH_BLOCK(gDecBlock, MR_DEC_TYPE(type2));
        fExp1->compileStatement(block, MR_CAST_ADDRESS(MR_INDEX_ADDRESS(address, MR_INT(0)), type1), index);
        fExp2->compileStatement(block, MR_CAST_ADDRESS(MR_INDEX_ADDRESS(address, MR_INT(size1)), type2), index);
    } else {
        // if shared
        block->fCode.push_back(MR_STORE(address, compileSample(index)));
    }
}

TValue* TConcat::compileSample(TIndex* index)
{
    int rate = getRate();
    TType* type = getType();
    TType* type1 = fExp1->getType();
    TType* type2 = fExp2->getType();
    int size1 = type1->getSize();
    int size2 = type2->getSize();

    // Declare output
#ifdef ALT_VECTOR
    TVectorAddress* new_out_vec = MR_VECTOR_ADDRESS(getFreshID("Concat"), type, rate * gVecSize);
#else
    TType* vec_type = MR_VECTOR_TYPE(type, rate * gVecSize);
    MR_PUSH_BLOCK(gDecBlock, MR_DEC_TYPE(vec_type));
    TNamedAddress* new_out_vec = MR_VECTOR_ADDRESS(getFreshID("Concat"), vec_type);
#endif

    // Compute new indexes
    TIndex* var_j = MR_VAR(getFreshID("j"));

    TBlockStatement* block = MR_BLOCK();

    MR_PUSH_BLOCK(gDecBlock, MR_DEC(new_out_vec));

    MR_PUSH_BLOCK(gDecBlock, MR_DEC_TYPE(type1));
    MR_PUSH_BLOCK(gDecBlock, MR_DEC_TYPE(type2));

    fExp1->compileStatement(block, MR_CAST_ADDRESS(MR_INDEX_ADDRESS(MR_INDEX_ADDRESS(new_out_vec, var_j), MR_INT(0)), type1), var_j);
    fExp2->compileStatement(block, MR_CAST_ADDRESS(MR_INDEX_ADDRESS(MR_INDEX_ADDRESS(new_out_vec, var_j), MR_INT(size1)), type2), var_j);

    gExternalBlock->fCode.push_back(MR_LOOP(rate * gVecSize, var_j, block));

    // Output type checking
    CHECK_EQUAL_TYPE(type, MR_INDEX_ADDRESS(new_out_vec, index)->getType());

    // Final value
    return MR_LOAD(MR_INDEX_ADDRESS(new_out_vec, index));
}

void TVectorAt::compileStatement(TBlockStatement* block, TAddress* address, TIndex* index)
{
    block->fCode.push_back(MR_STORE(address, compileSample(index)));
}

TValue* TVectorAt::compileSample(TIndex* index)
{
    TType* type = getType();

    TValue* res1 = fExp1->compileSample(index);
    TValue* res2 = fExp2->compileSample(index);

    TIntValue* id = dynamic_cast<TIntValue*>(res2);
    TLoadValue* val = dynamic_cast<TLoadValue*>(res1);

    assert(id && val);

    // Output type checking
    CHECK_EQUAL_TYPE(type, MR_INDEX_ADDRESS(val->fAddress, MR_INT(id->fValue))->getType());

    return MR_LOAD(MR_INDEX_ADDRESS(val->fAddress, MR_INT(id->fValue)));
}

void TDelayLine::compileStatement(TBlockStatement* block, TAddress* address, TIndex* index)
{

}

TValue* TDelayLine::compileSample(TIndex* index)
{

}

#ifdef ALT_VECTOR
TVectorAddress* TDelayLine::compile()
#else
TNamedAddress* TDelayLine::compile()
#endif
{
    int rate = getRate();
    TType* type = getType();

    // fMaxDelay is small

    // Declare output
#ifdef ALT_VECTOR
    TVectorAddress* new_out_vec = MR_VECTOR_ADDRESS(getFreshID("DelayLine"), type, rate * gVecSize);
#else
    TType* vec_type = MR_VECTOR_TYPE(type, rate * gVecSize);
    MR_PUSH_BLOCK(gDecBlock, MR_DEC_TYPE(vec_type));
    TNamedAddress* new_out_vec = MR_VECTOR_ADDRESS(getFreshID("DelayLine"), vec_type);
#endif

    // TODO : fill DL

    // Compute new indexes
    TIndex* var_j = MR_VAR(getFreshID("j"));

    TBlockStatement* block = MR_BLOCK();

    MR_PUSH_BLOCK(gDecBlock, MR_DEC(new_out_vec));

    fExp->compileStatement(block, MR_INDEX_ADDRESS(new_out_vec, MR_ADD(var_j, MR_INT(fMaxDelay))), var_j);
    gExternalBlock->fCode.push_back(MR_LOOP(rate * gVecSize, var_j, block));

    return new_out_vec;
}

void TDelayAt::compileStatement(TBlockStatement* block, TAddress* address, TIndex* index)
{
    block->fCode.push_back(MR_STORE(address, compileSample(index)));
}

TValue* TDelayAt::compileSample(TIndex* index)
{
    TType* type = getType();

    TDelayLine* delay_line = dynamic_cast<TDelayLine*>(fExp1);
    assert(delay_line);
#ifdef ALT_VECTOR
    TVectorAddress* new_out_vec = delay_line->compile();
#else
    TNamedAddress* new_out_vec = delay_line->compile();
#endif

    TValue* res2 = fExp2->compileSample(index);
    TIntValue* id = dynamic_cast<TIntValue*>(res2);

    // Output type checking
    CHECK_EQUAL_TYPE(type, MR_INDEX_ADDRESS(new_out_vec, MR_SUB(index, MR_INT(id->fValue)))->getType());

    return MR_LOAD(MR_INDEX_ADDRESS(new_out_vec, MR_SUB(index, MR_INT(id->fValue))));
}

// Recursive groups

map<string, int> TRecGroup::gRecCompEnv;
#ifdef ALT_VECTOR
map<string, TVectorAddress*> TRecGroup::gRecProjCompEnv;
#else
map<string, TNamedAddress*> TRecGroup::gRecProjCompEnv;
#endif
void TRecGroup::compileStatement(TBlockStatement* block, TAddress* address, TIndex* index)
{
    block->fCode.push_back(MR_STORE(address, compileSample(index)));
}

TValue* TRecGroup::compileSample(TIndex* index)
{
    TBlockStatement* block = MR_BLOCK();

    assert(fCode.size() > 0);
    int rate = fCode[0]->getRate();

    // If not yet compiled
    if (TRecGroup::gRecCompEnv.find(fRecGroup) == TRecGroup::gRecCompEnv.end()) {

        // Group is now compiled
        TRecGroup::gRecCompEnv[fRecGroup] = 1;

        // Compute new indexes
        TIndex* var_j = MR_VAR(getFreshID("j"));

        vector<TSignal*>::const_iterator it;
        int i = 0;
        for (it = fCode.begin(); it != fCode.end(); it++, i++) {

            TType* type = (*it)->getType();
        #ifdef ALT_VECTOR
            // Declare output
            TVectorAddress* new_out_vec;
        #else
            // Declare output
            TNamedAddress* new_out_vec;
        #endif
            // Look if projection is already compiled
            string rec_proj = subst("$0$1", fRecGroup, T(i));
            if (TRecGroup::gRecProjCompEnv.find(rec_proj) != TRecGroup::gRecProjCompEnv.end()) {
                new_out_vec = TRecGroup::gRecProjCompEnv[rec_proj];
            } else {

            #ifdef ALT_VECTOR
                new_out_vec = MR_VECTOR_ADDRESS(rec_proj, type, rate * gVecSize);
            #else
                TType* vec_type = MR_VECTOR_TYPE(type, rate * gVecSize);
                MR_PUSH_BLOCK(gDecBlock, MR_DEC_TYPE(vec_type));
                new_out_vec = MR_VECTOR_ADDRESS(rec_proj, vec_type);
            #endif

                MR_PUSH_BLOCK(gDecBlock, MR_DEC(new_out_vec));
                TRecGroup::gRecProjCompEnv[rec_proj] = new_out_vec;  // Insert compiled projection
                (*it)->compileStatement(block, MR_INDEX_ADDRESS(new_out_vec, var_j) , var_j);
            }
        }

        gExternalBlock->fCode.push_back(MR_LOOP(rate * gVecSize, var_j, block));

    }

    return MR_NULL();
}

void TRecProj::compileStatement(TBlockStatement* block, TAddress* address, TIndex* index)
{
    block->fCode.push_back(MR_STORE(address, compileSample(index)));
}

TValue* TRecProj::compileSample(TIndex* index)
{
    TType* type = getType();

    // Compile recursive group
    fRecGroup->compileSample(index);

    // Get the projection
    string rec_proj = subst("$0$1", fRecGroup->fRecGroup, T(fProj));
    assert(TRecGroup::gRecProjCompEnv.find(rec_proj) != TRecGroup::gRecProjCompEnv.end());

    // Output type checking
    CHECK_EQUAL_TYPE(type, MR_INDEX_ADDRESS(TRecGroup::gRecProjCompEnv[rec_proj], index)->getType());

    return MR_LOAD(MR_INDEX_ADDRESS(TRecGroup::gRecProjCompEnv[rec_proj], index));
}


