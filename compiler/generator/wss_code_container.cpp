/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include "wss_code_container.hh"
#include "fir_to_fir.hh"
#include "global.hh"

using namespace std;

#define WORK_STEALING_INDEX 0
#define LAST_TASK_INDEX 1
#define START_TASK_INDEX LAST_TASK_INDEX + 1
#define START_TASK_MAX 2

void WSSCodeContainer::moveCompute2ComputeThread()
{
    // Move stack variables from "compute" to "computeThread"
    struct Compute2ComputeThread : public DispatchVisitor {
        WSSCodeContainer* fContainer;
        vector<string>    fVariables;

        bool containVar(const string& name)
        {
            for (const auto& it : fVariables) {
                if (name.find(it) != string::npos) {
                    return true;
                }
            }
            return false;
        }

        void visit(DeclareVarInst* inst)
        {
            BasicCloneVisitor cloner;
            if (inst->fAddress->isStack() && containVar(inst->getName())) {
                // For local thread access (in computeThread)
                fContainer->pushComputeThread(inst->clone(&cloner));
                // Mark inst to be removed
                inst->fAddress->setAccess(Address::kLink);
            }

            // Then dispatch and possibly rewrite 'value' access
            DispatchVisitor::visit(inst);
        }

        Compute2ComputeThread(WSSCodeContainer* container, vector<string> variables)
            : fContainer(container), fVariables(variables)
        {
        }
    };

    // Transform stack variables in struct variables
    VariableMover::Move(this, "Rec");
    VariableMover::Move(this, "tmp");
    VariableMover::Move(this, "Zec");
    VariableMover::Move(this, "Yec");

    // To move variables in "computeThread"
    Compute2ComputeThread mover(this, {"fSoundfile", "Then", "Else", "Slow", "Vec", "fInput",
                                       "fOutput", "pfPerm", "pfTemp"});
    fComputeBlockInstructions->accept(&mover);

    // Remove marked variables from fComputeBlockInstructions
    RemoverCloneVisitor remover;
    fComputeBlockInstructions = static_cast<BlockInst*>(fComputeBlockInstructions->clone(&remover));
}

void WSSCodeContainer::generateDAGLoopWSSAux1(lclgraph dag, BlockInst* gen_code, int cur_thread)
{
    // Last stage connected to end task
    if (dag[0].size() > 1) {
        Values fun_args;
        fun_args.push_back(IB::genLoadStructVar("fScheduler"));
        fun_args.push_back(IB::genInt32NumInst(LAST_TASK_INDEX));
        fun_args.push_back(IB::genInt32NumInst(int(dag[0].size())));
        gen_code->pushBackInst(
            IB::genLabelInst("/* Initialize end task, if more than one input */"));
        gen_code->pushBackInst(IB::genVoidFunCallInst("initTask", fun_args));
    } else {
        gen_code->pushBackInst(
            IB::genLabelInst("/* End task has only one input, so will be directly activated */"));
    }

    // Compute init section
    gen_code->pushBackInst(
        IB::genLabelInst("/* Only initialize tasks with more than one input */"));
    for (int l = int(dag.size()) - 1; l >= 0; l--) {
        for (const auto& p : dag[l]) {
            if (p->getBackwardLoopDependencies().size() >
                1) {  // Only initialize tasks with more than 1 input,
                      // since tasks with one input are "directly"
                      // activated.
                Values fun_args;
                fun_args.push_back(IB::genLoadStructVar("fScheduler"));
                fun_args.push_back(IB::genInt32NumInst(p->getIndex()));
                fun_args.push_back(
                    IB::genInt32NumInst(int(p->getBackwardLoopDependencies().size())));
                gen_code->pushBackInst(IB::genVoidFunCallInst("initTask", fun_args));
            }
        }
    }

    Values fun_args1;
    fun_args1.push_back(IB::genLoadStructVar("fScheduler"));
    if (cur_thread == -1) {
        // Push ready tasks in each thread WSQ
        gen_code->pushBackInst(IB::genLabelInst("/* Push ready tasks in each thread WSQ */"));
        fun_args1.push_back(IB::genInt32NumInst(cur_thread));
    } else {
        // Push ready tasks in 'num_thread' WSQ
        gen_code->pushBackInst(IB::genLabelInst("/* Push ready tasks in 'num_thread' WSQ */"));
        fun_args1.push_back(IB::genLoadFunArgsVar("num_thread"));
    }
    gen_code->pushBackInst(IB::genVoidFunCallInst("initTaskList", fun_args1));
}

void WSSCodeContainer::generateDAGLoopWSSAux2(lclgraph dag, const string& counter)
{
    string     index     = "fIndex";
    BlockInst* loop_code = fComputeBlockInstructions;

    loop_code->pushBackInst(IB::genStoreStructVar(fFFullCount, IB::genLoadFunArgsVar(counter)));
    loop_code->pushBackInst(IB::genVolatileStoreStructVar(index, IB::genInt32NumInst(0)));

    generateDAGLoopWSSAux1(dag, loop_code, -1);  // -1 means dispath ready tasks on all WSQ

    Values fun_args1;
    fun_args1.push_back(IB::genLoadStructVar("fScheduler"));
    loop_code->pushBackInst(IB::genVoidFunCallInst("signalAll", fun_args1));

    Values fun_args2;
    if (fObjName != "this") {
        fun_args2.push_back(IB::genLoadFunArgsVar(fObjName));
    }
    fun_args2.push_back(IB::genInt32NumInst(0));
    loop_code->pushBackInst(IB::genVoidFunCallInst("computeThread" + fKlassName, fun_args2));

    loop_code->pushBackInst(IB::genVoidFunCallInst("syncAll", fun_args1));
}

void WSSCodeContainer::generateDAGLoopWSSAux3(int loop_count, const vector<int>& ready_loop)
{
    string index = "fIndex";

    // Needed in the struct
    pushDeclare(IB::genDecVolatileStructVar(index, IB::genInt32Typed()));
    pushDeclare(IB::genDecStructVar(fFFullCount, IB::genInt32Typed()));
    pushDeclare(IB::genDecStructVar("fScheduler", IB::genBasicTyped(Typed::kVoid_ptr)));

    // Scheduler prototypes declaration
    pushGlobalDeclare(IB::genLabelInst("#ifdef __cplusplus"));
    pushGlobalDeclare(IB::genLabelInst("extern \"C\""));
    pushGlobalDeclare(IB::genLabelInst("{"));
    pushGlobalDeclare(IB::genLabelInst("#endif"));

    pushGlobalDeclare(IB::genFunction2("createScheduler", Typed::kVoid_ptr, "task_queue_size",
                                       Typed::kInt32, "init_task_list_size", Typed::kInt32));
    pushGlobalDeclare(
        IB::genFunction1("deleteScheduler", Typed::kVoid, "scheduler", Typed::kVoid_ptr));
    pushGlobalDeclare(IB::genFunction2("startAll", Typed::kVoid, "scheduler", Typed::kVoid_ptr,
                                       "dsp", Typed::kVoid_ptr));
    pushGlobalDeclare(IB::genFunction1("stopAll", Typed::kVoid, "scheduler", Typed::kVoid_ptr));
    pushGlobalDeclare(IB::genFunction1("initAll", Typed::kVoid, "scheduler", Typed::kVoid_ptr));
    pushGlobalDeclare(IB::genFunction1("signalAll", Typed::kVoid, "scheduler", Typed::kVoid_ptr));
    pushGlobalDeclare(IB::genFunction1("syncAll", Typed::kVoid, "scheduler", Typed::kVoid_ptr));
    pushGlobalDeclare(IB::genFunction3("pushHead", Typed::kVoid, "scheduler", Typed::kVoid_ptr,
                                       "cur_thread", Typed::kInt32, "task", Typed::kInt32));
    pushGlobalDeclare(IB::genFunction2("getNextTask", Typed::kInt32, "scheduler", Typed::kVoid_ptr,
                                       "cur_thread", Typed::kInt32));
    pushGlobalDeclare(IB::genFunction3("initTask", Typed::kVoid, "scheduler", Typed::kVoid_ptr,
                                       "task_num", Typed::kInt32, "count", Typed::kInt32));
    pushGlobalDeclare(IB::genFunction4("activateOutputTask1", Typed::kVoid, "scheduler",
                                       Typed::kVoid_ptr, "cur_thread", Typed::kInt32, "task",
                                       Typed::kInt32, "task_num", Typed::kInt32_ptr));
    pushGlobalDeclare(IB::genFunction3("activateOutputTask2", Typed::kVoid, "scheduler",
                                       Typed::kVoid_ptr, "cur_thread", Typed::kInt32, "task",
                                       Typed::kInt32));
    pushGlobalDeclare(IB::genFunction4("activateOneOutputTask", Typed::kVoid, "scheduler",
                                       Typed::kVoid_ptr, "cur_thread", Typed::kInt32, "task",
                                       Typed::kInt32, "task_num", Typed::kInt32_ptr));
    pushGlobalDeclare(IB::genFunction3("getReadyTask", Typed::kVoid, "scheduler", Typed::kVoid_ptr,
                                       "cur_thread", Typed::kInt32, "task_num", Typed::kInt32_ptr));
    pushGlobalDeclare(IB::genFunction2("initTaskList", Typed::kVoid, "scheduler", Typed::kVoid_ptr,
                                       "cur_thread", Typed::kInt32));
    pushGlobalDeclare(IB::genFunction2("addReadyTask", Typed::kVoid, "scheduler", Typed::kVoid_ptr,
                                       "task_num", Typed::kInt32));

    pushGlobalDeclare(IB::genLabelInst("#ifdef __cplusplus"));
    pushGlobalDeclare(IB::genLabelInst("}"));
    pushGlobalDeclare(IB::genLabelInst("#endif"));

    // Specific allocate instructions
    Values fun_args;
    fun_args.push_back(IB::genInt32NumInst(loop_count));
    fun_args.push_back(IB::genInt32NumInst(int(ready_loop.size())));
    pushAllocateMethod(
        IB::genStoreStructVar("fScheduler", IB::genFunCallInst("createScheduler", fun_args)));

    for (size_t i = 0; i < ready_loop.size(); i++) {
        Values fun_args1;
        fun_args1.push_back(IB::genLoadStructVar("fScheduler"));
        fun_args1.push_back(IB::genInt32NumInst(ready_loop[i]));
        pushAllocateMethod(IB::genVoidFunCallInst("addReadyTask", fun_args1));
    }
    Values fun_args2;
    fun_args2.push_back(IB::genLoadStructVar("fScheduler"));
    fun_args2.push_back(IB::genLoadFunArgsVar(fObjName));
    pushAllocateMethod(IB::genVoidFunCallInst("startAll", fun_args2));

    // Specific destroy instructions
    Values fun_args4;
    fun_args4.push_back(IB::genLoadStructVar("fScheduler"));
    pushDestroyMethod(IB::genVoidFunCallInst("deleteScheduler", fun_args4));
}

void WSSCodeContainer::generateLocalInputs(BlockInst* loop_code, const string& index_string)
{
    // Generates line like: FAUSTFLOAT* fInput0 = &fInput0_ptr[index];
    Typed* type = IB::genArrayTyped(IB::genFloatMacroTyped(), 0);

    for (int index = 0; index < inputs(); index++) {
        string name1 = subst("input$0", T(index));
        string name2 = subst("fInput$0_ptr", T(index));
        loop_code->pushBackInst(IB::genDecStackVar(
            name1, type,
            IB::genLoadArrayStructVarAddress(name2, IB::genVolatileLoadStructVar(index_string))));
    }
}

void WSSCodeContainer::generateLocalOutputs(BlockInst* loop_code, const string& index_string)
{
    // Generates line like: FAUSTFLOAT* fOutput0 = &fOutput0_ptr[index];
    Typed* type = IB::genArrayTyped(IB::genFloatMacroTyped(), 0);

    for (int index = 0; index < outputs(); index++) {
        string name1 = subst("output$0", T(index));
        string name2 = subst("fOutput$0_ptr", T(index));
        loop_code->pushBackInst(IB::genDecStackVar(
            name1, type,
            IB::genLoadArrayStructVarAddress(name2, IB::genVolatileLoadStructVar(index_string))));
    }
}

BlockInst* WSSCodeContainer::generateDAGLoopWSS(lclgraph dag)
{
    string index = "fIndex";

    BlockInst* loop_code = fComputeThreadBlockInstructions;
    loop_code->pushBackInst(IB::genDecStackVar("tasknum", IB::genInt32Typed(),
                                               IB::genInt32NumInst(WORK_STEALING_INDEX)));

    DeclareVarInst* count_dec = IB::genDecStackVar("vsize", IB::genInt32Typed());

    ValueInst*    switch_cond  = IB::genLoadStackVar("tasknum");
    ::SwitchInst* switch_block = IB::genSwitchInst(switch_cond);

    // Work stealing task
    BlockInst* ws_block = IB::genBlockInst();
    ws_block->pushBackInst(IB::genLabelInst("/* Work Stealing task */"));
    Values fun_args2;
    fun_args2.push_back(IB::genLoadStructVar("fScheduler"));
    fun_args2.push_back(IB::genLoadFunArgsVar("num_thread"));

    ws_block->pushBackInst(
        IB::genStoreStackVar("tasknum", IB::genFunCallInst("getNextTask", fun_args2)));
    switch_block->addCase(WORK_STEALING_INDEX, ws_block);

    // Last task
    BlockInst* last_block = IB::genBlockInst();
    last_block->pushBackInst(IB::genLabelInst("/* Last task */"));
    last_block->pushBackInst(IB::genVolatileStoreStructVar(
        index, IB::genAdd(IB::genVolatileLoadStructVar(index), gGlobal->gVecSize)));

    ValueInst* if_cond =
        IB::genLessThan(IB::genVolatileLoadStructVar(index), IB::genLoadStructVar(fFFullCount));

    BlockInst* then_block = IB::genBlockInst();
    BlockInst* else_block = IB::genBlockInst();

    else_block->pushBackInst(IB::genRetInst());

    // Generates init DAG and ready tasks activations
    generateDAGLoopWSSAux1(dag, then_block);
    // last_block->pushBackInst(IB::genIfInst(if_cond, then_block, else_block));
    last_block->pushBackInst(IB::genIfInst(if_cond, then_block));

    // Generates tasknum
    last_block->pushBackInst(IB::genStoreStackVar("tasknum", IB::genInt32NumInst(0)));

    // Push if block as last_task
    switch_block->addCase(LAST_TASK_INDEX, last_block);

    // Generates global "switch/case"
    int loop_num = START_TASK_MAX;  // First index to be used for remaining tasks

    ValueInst* while_cond =
        IB::genLessThan(IB::genVolatileLoadStructVar(index), IB::genLoadStructVar(fFFullCount));
    BlockInst* switch_block_code = IB::genBlockInst();

    // Generates switch/case block "header"
    ValueInst* init1 = IB::genLoadStructVar(fFFullCount);
    ValueInst* init2 = IB::genSub(init1, IB::genVolatileLoadStructVar(index));
    Values     min_fun_args;
    min_fun_args.push_back(IB::genInt32NumInst(gGlobal->gVecSize));
    min_fun_args.push_back(init2);
    ValueInst* init3 = IB::genFunCallInst("min_i", min_fun_args);

    DeclareVarInst* count_store = IB::genDecStackVar("vsize", IB::genInt32Typed(), init3);

    // Generate input/output access
    generateLocalInputs(switch_block_code, index);
    generateLocalOutputs(switch_block_code, index);

    switch_block_code->pushBackInst(count_store);

    for (int l = int(dag.size()) - 1; l > 0; l--) {
        for (lclset::const_iterator p = dag[l].begin(); p != dag[l].end(); p++, loop_num++) {
            // Generates a "case" block for each task
            BlockInst* case_block = IB::genBlockInst();
            generateDAGLoopAux(*p, case_block, count_dec->load(), loop_num);

            // Add output tasks activation code

            // One output only
            if ((*p)->getForwardLoopDependencies().size() == 1) {
                case_block->pushBackInst(IB::genLabelInst("/* One output only */"));
                lclset::const_iterator p1 = (*p)->getForwardLoopDependencies().begin();
                if ((*p1)->getBackwardLoopDependencies().size() == 1) {
                    case_block->pushBackInst(
                        IB::genStoreStackVar("tasknum", IB::genInt32NumInst((*p1)->getIndex())));
                } else {
                    Values fun_args;
                    fun_args.push_back(IB::genLoadStructVar("fScheduler"));
                    fun_args.push_back(IB::genLoadFunArgsVar("num_thread"));
                    fun_args.push_back(IB::genInt32NumInst((*p1)->getIndex()));
                    fun_args.push_back(IB::genLoadStackVarAddress("tasknum"));
                    case_block->pushBackInst(
                        IB::genVoidFunCallInst("activateOneOutputTask", fun_args));
                }

            } else {
                CodeLoop* keep = nullptr;

                // Find one output with only one backward dependencies
                for (const auto& p1 : (*p)->getForwardLoopDependencies()) {
                    if (p1->getBackwardLoopDependencies().size() == 1) {
                        keep = p1;
                        break;
                    }
                }

                if (keep == nullptr) {
                    case_block->pushBackInst(
                        IB::genStoreStackVar("tasknum", IB::genInt32NumInst(WORK_STEALING_INDEX)));
                }

                for (const auto& p1 : (*p)->getForwardLoopDependencies()) {
                    if (p1->getBackwardLoopDependencies().size() == 1) {  // Task is the only input
                        if (p1 != keep) {
                            Values fun_args;
                            fun_args.push_back(IB::genLoadStructVar("fScheduler"));
                            fun_args.push_back(IB::genLoadFunArgsVar("num_thread"));
                            fun_args.push_back(IB::genInt32NumInst(p1->getIndex()));
                            case_block->pushBackInst(IB::genVoidFunCallInst("pushHead", fun_args));
                        }
                    } else {
                        if (keep == nullptr) {
                            Values fun_args;
                            fun_args.push_back(IB::genLoadStructVar("fScheduler"));
                            fun_args.push_back(IB::genLoadFunArgsVar("num_thread"));
                            fun_args.push_back(IB::genInt32NumInst(p1->getIndex()));
                            fun_args.push_back(IB::genLoadStackVarAddress("tasknum"));
                            case_block->pushBackInst(
                                IB::genVoidFunCallInst("activateOutputTask1", fun_args));
                        } else {
                            Values fun_args;
                            fun_args.push_back(IB::genLoadStructVar("fScheduler"));
                            fun_args.push_back(IB::genLoadFunArgsVar("num_thread"));
                            fun_args.push_back(IB::genInt32NumInst(p1->getIndex()));
                            case_block->pushBackInst(
                                IB::genVoidFunCallInst("activateOutputTask2", fun_args));
                        }
                    }
                }

                if (keep != nullptr) {
                    case_block->pushBackInst(
                        IB::genStoreStackVar("tasknum", IB::genInt32NumInst(keep->getIndex())));
                } else {
                    Values fun_args;
                    fun_args.push_back(IB::genLoadStructVar("fScheduler"));
                    fun_args.push_back(IB::genLoadFunArgsVar("num_thread"));
                    fun_args.push_back(IB::genLoadStackVarAddress("tasknum"));
                    case_block->pushBackInst(IB::genVoidFunCallInst("getReadyTask", fun_args));
                }
            }

            // Add the "case" block
            switch_block->addCase(loop_num, case_block);
        }
    }

    // Last stage
    lclset level = dag[0];

    if (level.size() == 1) {
        BlockInst* case_block = IB::genBlockInst();
        generateDAGLoopAux(*level.begin(), case_block, count_dec->load(), loop_num);
        case_block->pushBackInst(
            IB::genStoreStackVar("tasknum", IB::genInt32NumInst(LAST_TASK_INDEX)));
        // Add the "case" block
        switch_block->addCase(loop_num, case_block);
    } else {
        for (lclset::const_iterator p = level.begin(); p != level.end(); p++, loop_num++) {
            BlockInst* case_block = IB::genBlockInst();
            generateDAGLoopAux(*p, case_block, count_dec->load(), loop_num);

            Values fun_args;
            fun_args.push_back(IB::genLoadStructVar("fScheduler"));
            fun_args.push_back(IB::genLoadFunArgsVar("num_thread"));
            fun_args.push_back(IB::genInt32NumInst(LAST_TASK_INDEX));
            fun_args.push_back(IB::genLoadStackVarAddress("tasknum"));

            case_block->pushBackInst(IB::genVoidFunCallInst("activateOneOutputTask", fun_args));
            // Add the "case" block
            switch_block->addCase(loop_num, case_block);
        }
    }

    // Finishes switch block
    switch_block_code->pushBackInst(switch_block);
    WhileLoopInst* while_block = IB::genWhileLoopInst(while_cond, switch_block_code);

    // Add the "while" block
    loop_code->pushBackInst(while_block);
    return loop_code;
}

void WSSCodeContainer::processFIR(void)
{
    // Default FIR to FIR transformations
    CodeContainer::processFIR();

    // Transform some stack variables in struct variables, move some variables from "compute" to
    // "computeThread"
    moveCompute2ComputeThread();

    lclgraph    dag;
    vector<int> ready_loop;
    int         loop_count;
    CodeLoop::sortGraph(fCurLoop, dag);

    computeForwardDAG(dag, loop_count, ready_loop);

    generateDAGLoopWSSAux3(loop_count, ready_loop);

    // Prepare global loop
    fThreadLoopBlock = generateDAGLoopWSS(dag);

    generateDAGLoopWSSAux2(dag, fFullCount);

    if (gGlobal->gRemoveVarAddress) {
        VarAddressRemover remover;
        fComputeBlockInstructions       = remover.getCode(fComputeBlockInstructions);
        fThreadLoopBlock                = remover.getCode(fThreadLoopBlock);
        fComputeThreadBlockInstructions = remover.getCode(fComputeThreadBlockInstructions);
    }

    // Sort arrays to be at the begining
    // fComputeBlockInstructions->fCode.sort(sortArrayDeclarations);

    /*
    // Verify code
    CodeVerifier verifier;
    BlockInst global_block;
    // Declaration part
    global_block.merge(fExtGlobalDeclarationInstructions);
    global_block.merge(fGlobalDeclarationInstructions);
    global_block.merge(fDeclarationInstructions);
    // Init method
    global_block.merge(fInitInstructions);
    global_block.merge(fPostInitInstructions);
    global_block.merge(fStaticInitInstructions);
    global_block.merge(fPostStaticInitInstructions);
    // Compute method
    global_block.merge(fComputeBlockInstructions);
    global_block.pushBackInst(fDAGBlock);
    global_block.accept(&verifier);
    */
}

DeclareFunInst* WSSCodeContainer::generateComputeThread(const string& name, const string& obj,
                                                        bool ismethod, bool isvirtual)
{
    Names args;
    if (!ismethod) {
        args.push_back(IB::genNamedTyped(obj, Typed::kObj_ptr));
    }
    args.push_back(IB::genNamedTyped("num_thread", Typed::kInt32));

    BlockInst* block = IB::genBlockInst();
    block->pushBackInst(fThreadLoopBlock);

    // Explicit return
    block->pushBackInst(IB::genRetInst());

    // Creates function
    return IB::genVoidFunction(name, args, block, isvirtual);
}

DeclareFunInst* WSSCodeContainer::generateComputeThreadExternal(const string& name,
                                                                const string& obj)
{
    Names args;
    args.push_back(IB::genNamedTyped(obj, Typed::kVoid_ptr));
    args.push_back(IB::genNamedTyped("num_thread", Typed::kInt32));

    BlockInst* block = IB::genBlockInst();
    {
        Values args1;
        args1.push_back(
            IB::genCastInst(IB::genLoadFunArgsVar(obj), IB::genBasicTyped(Typed::kObj_ptr)));
        args1.push_back(IB::genLoadFunArgsVar("num_thread"));
        block->pushBackInst(IB::genVoidFunCallInst("computeThread" + fKlassName, args1));
    }

    // Explicit return
    block->pushBackInst(IB::genRetInst());

    // Creates function
    return IB::genVoidFunction(name, args, block, false);
}

BlockInst* WSSCodeContainer::flattenFIR(void)
{
    BlockInst* global_block = CodeContainer::flattenFIR();
    global_block->pushBackInst(IB::genLabelInst("========== Compute DSP Thread =========="));
    global_block->pushBackInst(fThreadLoopBlock);
    return global_block;
}
