#include "rust_instructions_compiler.hh"


RustInstructionsCompiler::RustInstructionsCompiler(CodeContainer* container) : InstructionsCompiler(container)
{

}


StatementInst* RustInstructionsCompiler::generateInitArray(const string& vname, Typed::VarType ctype, int delay)
{
  ValueInst* init = InstBuilder::genTypedZero(ctype);
  BasicTyped* typed = InstBuilder::genBasicTyped(ctype);
  string      index = gGlobal->getFreshID("l");

  // Generates table declaration
  pushDeclare(InstBuilder::genDecStructVar(vname, InstBuilder::genArrayTyped(typed, delay)));

  ValueInst* upperBound = InstBuilder::genInt32NumInst(delay);
  // Generates init table loop
  SimpleForLoopInst* loop = InstBuilder::genSimpleForLoopInst(index, upperBound);

  LoadVarInst* loadVarInst = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop));
  loop->pushFrontInst(InstBuilder::genStoreArrayStructVar(vname, loadVarInst, init));
  return loop;
}

StatementInst* RustInstructionsCompiler::generateShiftArray(const string& vname, int delay)
{
    string index = gGlobal->getFreshID("j");

    ValueInst* upperBound = InstBuilder::genInt32NumInst(delay+1);
    ValueInst* lowerBound = InstBuilder::genInt32NumInst(0);
    SimpleForLoopInst* loop        = InstBuilder::genSimpleForLoopInst(index, upperBound, lowerBound, true);
    LoadVarInst* loadVarInst = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop));
    ValueInst*   load_value2 = InstBuilder::genSub(loadVarInst, InstBuilder::genInt32NumInst(1));
    ValueInst*   load_value3 = InstBuilder::genLoadArrayStructVar(vname, load_value2);

    loop->pushFrontInst(InstBuilder::genStoreArrayStructVar(vname, loadVarInst, load_value3));
    return loop;
}

StatementInst* RustInstructionsCompiler::generateCopyArray(const string& vname_to, const string& vname_from, int size)
{
    string index = gGlobal->getFreshID("j");

    ValueInst* upperBound = InstBuilder::genInt32NumInst(size);
    SimpleForLoopInst* loop       = InstBuilder::genSimpleForLoopInst(index, upperBound);
    LoadVarInst* loadVarInst = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop));
    ValueInst*   load_value = InstBuilder::genLoadArrayStructVar(vname_from, loadVarInst);

    loop->pushFrontInst(InstBuilder::genStoreArrayStackVar(vname_to, loadVarInst, load_value));
    return loop;
}
